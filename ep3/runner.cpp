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

        std::cout << curr.next_time() << " [" <<  curr.name << "]: ";

        if (curr.current_task == -1) {
            curr.memory_init = Memory::manager->allocate(curr.id, curr.memory/Memory::block);
            Helper::assert(curr.memory_init != Memory::total/Memory::block, "Could not allocate memory! Exiting.");
        } else if (curr.current_task == int(curr.task.size())) {
            Memory::manager->free(curr.memory_init, curr.memory);
            continue;
        } else {
            Task & curr_task = curr.task[curr.current_task];
            Memory::manager->visit(curr.memory_init + curr_task.memory/Memory::block);
        }

        curr.current_task++;
        pq.push(curr);
    }

    std::cout << "Finish" << std::endl;
}
