#ifndef DEBUG_MAC442
#define DEBUG_MAC442

#include <stdio.h>

int debug_flag;

#define debug(...) {if (debug_flag) fprintf(stderr, __VA_ARGS__);}

#endif
