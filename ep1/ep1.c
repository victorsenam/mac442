#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "fcfs.h"

int scheduler_id;

int main (int argc, char * argv[]) {
    int i;

    /* Reading command parameters */
    if (argc < 4) {
        fprintf(stderr, "Fatal Error: Not enough parameters\n");
        return 1;
    }

    sscanf(argv[1], "%d", &scheduler_id);
    freopen(stdin, "r", argv[2]);
    freopen(stdout, "w", argv[3]);

    // checking for optional debug flag
    debug_flag = 0;
    for (i = 4; i < argc; i++)
        debug_flag |= (strlen(argv[i]) == 1 && argv[i][0] == 'd');
    
    return 0;
}
