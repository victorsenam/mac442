// IMPLEMENTS FIRST FIT ALGORITHM
#ifndef EP3_MEMORY_FIRST
#define EP3_MEMORY_FIRST

#include "memory.h"
#include <vector>
#include "binaryio.h"

class MemoryFirst : public Memory::Algorithm {
    virtual unsigned find_free_space (unsigned blocks);
};

#endif
