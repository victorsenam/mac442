#include "runner.h"

void Runner::execute () {
    std::priority_queue<Process> pq;    

    for (Process pr : Process::v)
        pq.push(pr);

    while (!pq.empty()) {
        Process curr = pq.top();
        pq.pop();

        std::cout << curr.name << " on task " << curr.current_task << "/" << curr.task.size() << std::endl;

        curr.current_task++;
        if (curr.current_task <= int(curr.task.size()))
            pq.push(curr);
    }

    std::cout << "Finish" << std::endl;
}
