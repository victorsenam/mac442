#include "memory_stub.h"

unsigned MemoryStub::allocate (unsigned pid, unsigned blocks) {
    std::cout << "allocate " << blocks << " blocks to " << pid << std::endl;
    return 0u;
}

void MemoryStub::visit (unsigned pid, unsigned block) {
    std::cout << pid << " visiting block " << block << std::endl;
}

void MemoryStub::free (unsigned initial_block, unsigned blocks) {
    std::cout << "free " << blocks << " blocks from " << initial_block << std::endl;
}
