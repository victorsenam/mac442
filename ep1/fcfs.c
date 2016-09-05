#include "fcfs.h"

int fcfs_main() {
	int current_task = 0;
	clock_t initial_clock = clock();
	int return_status;

	queue_init();

	while (process_running || current_task < task_n || queue_n) {
		double current_time = get_sec(initial_clock, clock());
		// check trace for incoming tasks
		if (current_time >= task_tasks[current_task].start_time) {
			queue_add(task_tasks + current_task);
			current_task++;
		}

		// assigns a new process to a runner, if possible
		if (process_running < 1 && queue_n) {
			if ((return_status = fcfs_assign())) {
				return return_status;
			}
		}
	}

	queue_deinit();

	return 0;
}

int fcfs_assign () {
	task_obj * curr = queue_top();
	queue_pop();

	curr->running = 1;
	process_running++;

	if (pthread_create(&(curr->thread), NULL, process_runner, curr)) {
		fprintf(stderr, "Fatal Error: Could not create thread: %s\n", curr->name);
		return 2;
	}

	return 0;
}
