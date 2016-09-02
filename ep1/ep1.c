#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "debug.h"
#include "task.h"

int scheduler_id;

double get_sec (clock_t a, clock_t b) {
    return ((double)(b-a))/CLOCKS_PER_SEC;
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
        debug_flag |= (argv[i][0] == 'd' && !argv[i][1]);

    // reading tasks
    debug("%d\n", task_n);
    debug("Sena otário\n");
    task_init();
    while (task_read());

    for (i = 0; i < task_n; i++) {
        debug("Adding task %s #%d at %f\n", task_tasks[i].name, i, get_sec(clock_init, clock()));
        sleep(1);
    }

    task_deinit();
    
}
