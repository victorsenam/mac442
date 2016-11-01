/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <limits>

#include "process.h"
#include "task.h"

int mem_total, mem_virtual;
int block_size, page_size;

int main (int argc, char * argv[]) {
    std::fstream trace(argv[1], std::ios::in);
    
    trace >> mem_total >> mem_virtual >> block_size >> page_size;

    trace.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    process curr_proc;
    for (std::string line; std::getline(trace, line);) {
        std::istringstream stream(line);
        stream >> curr_proc.time_init;
        stream >> curr_proc.name;
        stream >> curr_proc.time_end; 
        stream >> curr_proc.memory;
        std::cout << "proc: " << curr_proc.name << std::endl;

        for (task curr_task; stream >> curr_task.mem;) {
            stream >> curr_task.time;

            std::cout << "task: " << curr_task.mem << " " << curr_task.time << std::endl;
            curr_proc.tasks.push_back(curr_task);
        }
    }
       
}
