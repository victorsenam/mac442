#include "process.h"

void * process_runner (void * task_ref) {
    task_obj * task = (task_obj *) task_ref;
    clock_t last_clock, current_clock;

    last_clock = clock();

    while (task->remaining_time > 0.) {
        current_clock = clock();
        if (task->running) {
            task->remaining_time -= get_sec(last_clock, current_clock);
        }
        last_clock = current_clock;
    }

    task_stop(task);
    debug("Processo #%d [%s] finalizado (%d linha da saída)\n", task->id, task->name, task_complete_count++);
    printf("%s %f %f\n", task->name, seconds_past(&main_initial_time), seconds_past(&task->initial_time));
    
    return NULL;
}
