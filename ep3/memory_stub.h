#ifndef EP3_MEMORY_STUB
#define EP3_MEMORY_STUB

#include "memory.h"
#include <iostream>

class MemoryStub : public Memory::Algorithm {
    virtual unsigned allocate (unsigned size);
    virtual void visit (unsigned position);
};

#endif
