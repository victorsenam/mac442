/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#ifndef EP3_RUNNER
#define EP3_RUNNER

#include "helper.h"

#include "process.h"
#include "task.h"

#include "memory.h"
#include "page.h"

#include "binaryio.h"

#include <queue>
#include <cstdio>
#include <string>
#include <ctime>

class Runner {
public: 
    static void execute (unsigned interval);

private:
    static void dump_memory (BinaryIO * mem, unsigned size, std::string name, bool printused = false);
    static void dump_all (unsigned time);

    static const unsigned r_interval = 4u;
};

#endif
