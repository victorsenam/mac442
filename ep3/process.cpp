#include "process.h"

std::vector<Process> Process::v;

/** Null constructor **/
Process::Process () {}

/** Constructor from input line **
 * @param line
 * > input line relative to process
 * 
 * creates process described in line and inserts
 * it in Process::v
 */
Process::Process (std::string line) {
    std::istringstream stream(line);
    id = v.size();

    stream >> time;
    stream >> name;
    stream >> ending;
    stream >> memory;

    v.push_back(*this);
    std::cout << id << std::endl;
}
