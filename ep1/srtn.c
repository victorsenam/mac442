#include "srtn.h"

int srtn_main() {
	int current_task = 0;
	clock_t initial_clock = clock();
	int return_status;

    queue_init();

	while (task_running || current_task < task_n || queue_n) {
		double current_time = get_sec(initial_clock, clock());
		// check trace for incoming tasks
		if (current_task < task_n && current_time >= task_tasks[current_task].start_time) {

            if (queue_n && queue_top()->remaining_time > task_tasks[current_task].remaining_time) {
                task_stop(queue_top());
            }
            queue_add(task_tasks + current_task);
			current_task++;
		}

		// assigns a new process to a runner, if possible
		if (!task_running && queue_n) {
			if ((return_status = srtn_assign())) {
                return return_status;
			}
		}
	}

	return 0;
}

int srtn_assign () {
	task_obj * curr = queue_top();

    if (curr->remaining_time <= 0.) {
        queue_pop();
        return 0;
    }

    task_run(curr);

    if (curr->has_thread) 
        return 0;

    curr->has_thread = 1;
	if (pthread_create(&(curr->thread), NULL, process_runner, curr)) {
		fprintf(stderr, "Fatal Error: Could not create thread: %s\n", curr->name);
		return 2;
	}

	return 0;
}
