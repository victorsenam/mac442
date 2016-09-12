#ifndef DEBUG_MAC442
#define DEBUG_MAC442

#include <stdio.h>
#include <time.h>

int debug_flag;

void debug_print_time ();

#define debug(...) {if (debug_flag) {debug_print_time(); fprintf(stderr, __VA_ARGS__);}}

#endif
