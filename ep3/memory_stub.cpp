#include "memory_stub.h"

unsigned MemoryStub::allocate (unsigned size) {
    std::cout << "Allocating size " << size << std::endl;
    return 0u;
}

void MemoryStub::visit (unsigned position) {
    std::cout << "Visiting position " << position << std::endl;
}
