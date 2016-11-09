/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "trace.h"

void Trace::read (std::string file_name) {
    //process_v.clear();
    //task_qt = 0;

    std::fstream trace(file_name, std::ios::in);

    trace >> Memory::total >> Memory::virt >> Memory::block >> Memory::page;
    trace.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    while (std::getline(trace, line))
        Process proc(line);
}
