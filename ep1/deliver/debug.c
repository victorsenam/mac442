#include "debug.h"

void debug_print_time () {
    time_t currtime;
    char * buff;
    int n;

    time(&currtime);
    buff = ctime(&currtime);
    for (n = 0; buff[n]; n++);
    buff[--n] = 0;

    fprintf(stderr, "[%s] ", buff);
}
