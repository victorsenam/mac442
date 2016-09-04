#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "debug.h"
#include "helper.h"
#include "task.h"
#include "process.h"

int scheduler_id;

int main (int argc, char * argv[]) {
    int i;
    //clock_t clock_init = clock();
    
    /* Reading command parameters */
    if (argc < 4) {
        fprintf(stderr, "Fatal Error: Not enough parameters\n");
        return 1;
    }

    sscanf(argv[1], "%d", &scheduler_id);
    freopen(argv[2], "r", stdin);
    freopen(argv[3], "w", stdout);

    // checking for optional debug flag
    debug_flag = 0;
    for (i = 4; i < argc; i++)
        debug_flag |= (argv[i][0] == 'd' && !argv[i][1]);

    // reading tasks
    task_init();
    while (task_read());

    for (i = 0; i < task_n; i++) {
        int * arg = malloc(sizeof(*arg));
        *arg = i;

        if (pthread_create(&(task_tasks[i].thread), NULL, process_runner, arg)) {
            fprintf(stderr, "Fatal Error: Could not create thread %d\n", i);
            return 2;
        }
    }

    for (int i = 0; i < task_n; i++) {
        if (pthread_join(task_tasks[i].thread, NULL)) {
            fprintf(stderr, "Fatal Error: Could not join thread %d\n", i);
            return 3;
        }
    }

    task_deinit();
}
