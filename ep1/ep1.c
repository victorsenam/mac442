#include "debug.h"
#include "helper.h"
#include "task.h"
#include "fcfs.h"
#include "srtn.h"
#include "mqs.h"
#include "process.h"
#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char * argv[]) {
    int i;
    int scheduler_id;
    int main_loop_status;
    
    clock_gettime(CLOCK_REALTIME, &main_initial_time);

    /* Reading command parameters */
    if (argc < 4) {
        fprintf(stderr, "Fatal Error: Not enough parameters\n");
        return 1;
    }

    sscanf(argv[1], "%d", &scheduler_id);
    freopen(argv[2], "r", stdin);
    outbuff = fopen(argv[3], "w");

    // checking for optional debug flag
    debug_flag = 0;
    for (i = 4; i < argc; i++)
        debug_flag |= (argv[i][0] == 'd' && !argv[i][1]);

    // reading tasks
    task_init();
    while (task_read());

    // calling main loop
    if (scheduler_id == 1) {
        main_loop_status = fcfs_main();
    } else if (scheduler_id == 2) {
        main_loop_status = srtn_main();
    } else if (scheduler_id == 3) {
        main_loop_status =  mqs_main();
    } else {
        fprintf(stderr, "Fatal Error: Unrecognized Scheduler id %d\n", scheduler_id);
        return 4;
    }

    if (main_loop_status) {
        return main_loop_status;
    }

    for (int i = 0; i < task_n; i++) {
        if (pthread_join(task_tasks[i].thread, NULL)) {
            fprintf(stderr, "Fatal Error: Could not join thread %d\n", i);
            return 3;
        }
    }

    debug("Fim da simulação. Ocorreram %d mudanças de contexto.\n", task_context_change_count);
    fprintf(outbuff, "%d\n", task_context_change_count);

    printf("%d %d\n", task_context_change_count, task_deadline_fail_count);

    task_deinit();
    fclose(outbuff);
}
