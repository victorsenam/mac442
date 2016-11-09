#ifndef EP3_PROCESS
#define EP3_PROCESS

#include <vector>
#include <string>
#include <sstream>

#include <iostream>

#include "task.h"

class Task;
class Process {
public:
// Static
    static std::vector<Process> v;

    Process ();
    Process (std::string line);

// Member
    unsigned id;
    unsigned time;
    unsigned ending;
    unsigned memory;
    std::string name;
    std::vector<Task> task;
};

#endif
