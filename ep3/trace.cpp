/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "trace.h"

void read_trace (std::string file_name) {
    process_v.clear();
    task_qt = 0;

    std::fstream trace(file_name, std::ios::in);

    trace >> memory_total >> memory_virtual >> memory_block >> memory_page;
    trace.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string line;
    while (std::getline(trace, line);)
        process_v.push_back(process(line, process_v.size()));

    for (process pr : process_v)
        pr.print();
}
