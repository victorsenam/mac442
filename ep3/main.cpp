/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <limits>

#include "process.h"
#include "task.h"

void run (std::string file_name, int alg_mem, int alg_page, int debug_interval) {
    int mem_total, mem_virtual, block_size, page_size;

    // Reading Input
    std::fstream trace(file_name, std::ios::in);

    trace >> memory_total >> memory_virtual >> memory_block >> memory_page;
    trace.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (std::string line; std::getline(trace, line);) {
        process_v.push_back(process(line, process_v.size()));
    }

    for (process pr : process_v) {
        pr.print();
    }
}

int main (int argc, char * argv[]) {
    assert(argc == 5);
    run(argv[1], argv[2][0]-'0', argv[3][0]-'0', atoi(argv[4]));
}
