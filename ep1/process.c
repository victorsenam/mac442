#include "process.h"

void * process_runner (void * task_ref) {
    task_obj * task = (task_obj *) task_ref;
    clock_t last_clock, current_clock;

    debug("Task %s started\n", task->name);

    last_clock = clock();

    while (task->remaining_time > 0.) {
        current_clock = clock();
        if (task->running) {
            task->remaining_time -= get_sec(last_clock, current_clock);
        }
        last_clock = current_clock;
    }

    debug("Task %s finished\n", task->name);
    task_stop(task);
    
    return NULL;
}
