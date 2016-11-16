#ifndef EP3_RUNNER
#define EP3_RUNER

#include "helper.h"

#include "process.h"
#include "task.h"

#include "memory.h"
#include "page.h"

#include "binaryio.h"

#include <queue>
#include <cstdio>
#include <string>

class Runner {
public: 
    static void execute (unsigned interval);

private:
    static void dump_memory (BinaryIO * mem, unsigned size, std::string name, bool printused = false);
    static void dump_all (unsigned time);

};

#endif
