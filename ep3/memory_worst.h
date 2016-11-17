// IMPLEMENTS WORST FIT ALGORITHM
#ifndef EP3_MEMORY_WORST
#define EP3_MEMORY_WORST

#include "memory.h"

class MemoryWorst : public Memory::Algorithm {
    virtual unsigned find_free_space (unsigned blocks);
};

#endif
