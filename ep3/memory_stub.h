#ifndef EP3_MEMORY_STUB
#define EP3_MEMORY_STUB

#include "memory.h"
#include <iostream>

class MemoryStub : public Memory::Algorithm {
    unsigned allocate (unsigned pid, unsigned blocks);
    void visit (unsigned pid, unsigned block);
    void free (unsigned initial_block, unsigned blocks);
};

#endif
