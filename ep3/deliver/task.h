/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#ifndef EP3_TASK
#define EP3_TASK

#include "process.h"

class Process;
class Task {
public:
// Static
    static unsigned quant;

    Task (Process * owner);

// Member
    unsigned id;
    unsigned memory;
    unsigned time;
    Process * process;
};

#endif
