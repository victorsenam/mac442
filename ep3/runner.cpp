#include "runner.h"

void Runner::execute () {
    Memory::reinit();
    Page::reinit();

    std::priority_queue<Process> pq;

    for (Process pr : Process::v)
        pq.push(pr);

    while (!pq.empty()) {
        Process curr = pq.top();
        pq.pop();

        if (curr.current_task == -1) {
            unsigned blocks_necessary = (curr.memory+Memory::block-1)/Memory::block;
            unsigned available_space = Memory::manager->find_free_space(blocks_necessary);

            Memory::manager->reserve(curr, blocks_necessary, available_space);
            Helper::assure(curr.first_block < Memory::total/Memory::block, "Could not allocate memory! Exiting.");
        } else if (curr.current_task == int(curr.task.size())) {
            Memory::manager->free(curr.first_block, curr.memory);
            continue;
        } else {
            Task & curr_task = curr.task[curr.current_task];
            Memory::manager->visit(curr.id, curr.first_block*Memory::block + curr_task.memory);
        }

        curr.current_task++;
        pq.push(curr);
    }
}
