#ifndef EP3_PROCESS
#define EP3_PROCESS

#include "task.h"
#include <string>
#include <vector>

struct process_struct ;
typedef struct process_struct {
    // basic info
    int id;
    int time_init;
    int time_end;
    std::string name;

    // tasks
    std::vector<task> task;
} process;

#endif
