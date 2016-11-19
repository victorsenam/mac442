#include "runner.h"

void Runner::dump_memory (BinaryIO * mem, unsigned size, std::string name, bool printused) {
    printf("Bloco      ");
    if (printused)
        printf("|Usado? |");
    else
        printf("        |");
    printf("Conteúdo na %s", name.c_str());
    for (unsigned i = 0; i < size; i++) {
        if (i%Memory::block == 0) {
            printf("\n%-10u ", i/Memory::block);
            if (printused && Memory::used[i/Memory::block])
                printf("|  Sim  |");
            else
                printf("|       |");
        }
        printf(" % 10d", mem->read(i));
    }
    putchar('\n');
}

void Runner::dump_all (unsigned time) {
    printf("==== Estado da Memória: %us ====\n", time);
    Runner::dump_memory(Memory::io_virtual, Memory::virt, "Memória Virtual", true);
    Runner::dump_memory(Memory::io_physical, Memory::total, "Memória Física");
}

void Runner::execute (unsigned interval) {
    Page::reinit();
    Memory::reinit();

    std::priority_queue<Process> pq;

    unsigned next_print = 0;
    unsigned next_r = 0;
    unsigned next_p = 0;

    for (Process pr : Process::v)
        pq.push(pr);

    while (!pq.empty()) {
        Process curr = pq.top();
        pq.pop();

        while (interval && next_print <= curr.next_time().first) {
            Runner::dump_all(next_print);
            next_print += interval;
        }

        while (r_interval && next_r <= curr.next_time().first) {
            Page::reset_r();
            next_r += r_interval;
        }

        while (next_p <= curr.next_time().first) {
            Page::manager->signal();
            next_p++;
        }

        if (curr.current_task == -1) {
            unsigned blocks_necessary = (curr.memory+Memory::block-1)/Memory::block;
            unsigned available_space = Memory::manager->find_free_space(blocks_necessary);

            Memory::reserve(curr, blocks_necessary, available_space);
            Helper::assure(curr.first_block < Memory::virt/Memory::block, "Could not allocate memory! Exiting.");
        } else if (curr.current_task == int(curr.task.size())) {
            unsigned blocks_necessary = (curr.memory+Memory::block-1)/Memory::block;
            Memory::free(curr.first_block, blocks_necessary);
            continue;
        } else {
            Task & curr_task = curr.task[curr.current_task];
            Page::manager->visit(curr.id, curr.first_block*Memory::block + curr_task.memory);
        }

        curr.current_task++;
        pq.push(curr);
    }

    Page::finish();

    if (interval)
        Runner::dump_all(next_print);

}
