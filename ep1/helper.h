#ifndef HELPER_MAC442
#define HELPER_MAC442

#include <time.h>

struct timespec main_initial_time;
double get_sec (clock_t a, clock_t b);
double seconds_past (struct timespec * a);

#endif
