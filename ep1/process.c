#include "process.h"

void * process_runner (void * idx) {
    int id = *((int *) idx);
    task_obj * task = (task_tasks + id);
    clock_t last_clock, current_clock;

    debug("Task %s (#%d) started\n", task->name, id);

    task->remaining_time = task->duration;

    last_clock = clock();

    while (task->remaining_time > 0.) {
        current_clock = clock();
        if (task->running) {
            task->remaining_time -= get_sec(last_clock, current_clock);
        }
        last_clock = current_clock;
    }

    debug("Task %s (#%d) finished\n", task->name, id);
    
    return NULL;
}
