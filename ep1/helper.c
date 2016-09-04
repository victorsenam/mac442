#include "helper.h"

double get_sec (clock_t a, clock_t b) {
    return ((double)(b-a))/CLOCKS_PER_SEC;
}
