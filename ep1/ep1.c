#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "debug.h"
#include "fcfs.h"
#include "task.h"

int scheduler_id;

double get_sec (clock_t a, clock_t b) {
    return (b-a)/CLOCKS_PER_SEC;
}

int main (int argc, char * argv[]) {
    int i;
    clock_t clock_init = clock();

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
        debug_flag |= (strlen(argv[i]) == 1 && argv[i][0] == 'd');

    // reading tasks
    task_init();
    while (task_read());

    i = 0;
    while (i < task_n) {
        if (get_sec(clock_init, clock()) >= task_tasks[i].t0) {
            debug("task %s [#%d] entrou na fila\n", task_tasks[i].name, i);
            i++;
        }
    }

    task_deinit();
    
}
