#include "fcfs.h"

int fcfs_main() {
	int current_task = 0;
    int next_task = 0;
	clock_t initial_clock = clock();
	int return_status;

	while (task_running || current_task < task_n || next_task < task_n) {
		double current_time = get_sec(initial_clock, clock());
		// check trace for incoming tasks
		if (current_task < task_n && current_time >= task_tasks[current_task].start_time) {
            debug("Processo #%d [%s] chegou no sistema\n", task_tasks[current_task].id, task_tasks[current_task].name);
            clock_gettime(CLOCK_REALTIME, &task_tasks[current_task].initial_time);
			current_task++;
		}

		// assigns a new process to a runner, if possible
		if (!task_running && next_task < current_task) {
			if ((return_status = fcfs_assign(next_task))) {
				return return_status;
			}
            next_task++;
		}
	}

	return 0;
}

int fcfs_assign (int idx) {
	task_obj * curr = task_tasks + idx;

	task_run(curr);

    curr->has_thread = 1;
	if (pthread_create(&(curr->thread), NULL, process_runner, curr)) {
		fprintf(stderr, "Fatal Error: Could not create thread: %s\n", curr->name);
		return 2;
	}

	return 0;
}
