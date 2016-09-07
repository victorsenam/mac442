#include "mqs.h"

int mqs_main() {
	int current_task = 0;
	clock_t initial_clock = clock();
	int return_status;

    mqs_queue_init();

	while (task_running || current_task < task_n || mqs_queue_front != mqs_queue_back) {
		double current_time = get_sec(initial_clock, clock());
		// check trace for incoming tasks
		if (current_task < task_n && current_time >= task_tasks[current_task].start_time) {
            mqs_queue_add(task_tasks + current_task);
			current_task++;
		}
        // check if quantum of current task is done
        if (mqs_queue_front != mqs_queue_back && mqs_queue_current_queue()*QUANTUM < get_sec(mqs_queue_front_start_time, clock())) {
            task_stop(mqs_queue_top());
            // Promote queue front
            mqs_queue_promote_top();
        }

		// assigns a new process to a runner, if possible
		if (!task_running && mqs_queue_front != mqs_queue_back) {
			if ((return_status = mqs_assign())) {
                return return_status;
			}
		}
	}

	return 0;
}

int mqs_assign () {
	task_obj * curr = mqs_queue_top();

    if (curr->remaining_time <= 0.) {
        mqs_queue_pop();
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
