// IMPLEMENTS BEST FIT ALGORITHM
#ifndef EP3_MEMORY_BEST
#define EP3_MEMORY_BEST

#include "memory.h"

class MemoryBest : public Memory::Algorithm {
    virtual unsigned find_free_space (unsigned blocks);
};

#endif
