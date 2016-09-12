#include "helper.h"

double get_sec (clock_t a, clock_t b) {
    return ((double)(b-a))/CLOCKS_PER_SEC;
}

double seconds_past (struct timespec * a) {
    struct timespec curr;
    double res;
    clock_gettime(CLOCK_REALTIME, &curr);

    res = difftime(curr.tv_sec, a->tv_sec);
    res += ((double) (curr.tv_nsec - a->tv_nsec))*1e-9;
    return res;
}
