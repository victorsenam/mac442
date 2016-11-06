#ifndef EP3_PROCESS
#define EP3_PROCESS

#include "task.h"
#include <string>
#include <vector>
#include <cassert>
#include <sstream>

class process {
public:
    // basic info
    unsigned int id;
    unsigned int time_init;
    unsigned int time_end;
    unsigned int memory;
    std::string name;

    // tasks
    std::vector<task> tasks;
    unsigned int current_task;

    // constructors
    process (std::string line, unsigned int idx) {
        std::istringstream stream(line);

        id = idx;

        stream >> time_init;
        stream >> name;
        stream >> time_end; 
        stream >> memory;

        for (task curr_task; stream >> curr_task.mem;) {
            stream >> curr_task.time;
            curr_task.id = task_qt++;
            tasks.push_back(curr_task);
        }
    }

    process (int idx, int init, int end, int mem, std::string nm) {
        id = idx;
        time_init = init;
        time_end = end;
        memory = mem;
        name = nm;

        current_task = unsigned(-1);
    }

    // auxiliary methods
    unsigned int get_next_time () const {
        if (current_task+1 == 0) {
            return time_init;
        } else if (current_task == tasks.size()) {
            return time_end;
        } else {
            return tasks[current_task].time;
        }
    }

    void print () {
        printf("process [%u]%s:", id, name.c_str());
        for (task t : tasks)
            printf(" %u", t.id);
        printf("\n");
    }

    // compare for priority_queue
    bool operator < (const process & ot) const {
        return get_next_time() > ot.get_next_time();
    }
};

std::vector<process> process_v;

#endif
