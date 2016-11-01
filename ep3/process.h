#ifndef EP3_PROCESS
#define EP3_PROCESS

#include "task.h"
#include <string>
#include <vector>

struct process_struct ;
typedef struct process_struct {
    // basic info
    unsigned int time_init;
    unsigned int time_end;
    unsigned int memory;
    std::string name;

    // tasks
    std::vector<task> tasks;
} process;

std::vector<process> process_v;

#endif
