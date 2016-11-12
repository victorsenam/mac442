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

    unsigned aux;
    while (stream >> aux) {
        Task curr_task(this);
        curr_task.memory = aux;
        stream >> curr_task.time;
        curr_task.id = Task::quant++;
        this->task.push_back(curr_task);
    }

    current_task = -1;

    v.push_back(*this);
}

unsigned Process::next_time () const {
    if (current_task == -1)
        return time;
    if (current_task >= int(task.size()))
        return ending;
    return task[current_task].time;
}

bool Process::operator < (const Process & ot) const {
    return next_time() > ot.next_time();
}
