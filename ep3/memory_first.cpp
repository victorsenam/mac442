#include "memory_first.h"

unsigned MemoryFirst::find (unsigned pid, unsigned blocks) {
    unsigned ls = 0;
    
    for (unsigned i = 0; i < Memory::total/Memory::block; i++) {
        if (Memory::used[i]) ls = i+1;
        else if (ls - i + 1 >= blocks)
            return ls;
    }

    return Memory::total/Memory::block;
}

unsigned MemoryFirst::allocate (unsigned pid, unsigned blocks) {
    unsigned beg = MemoryFirst::find(pid, blocks);
    if (beg != Memory::total/Memory::block) {
        for (unsigned i = 0; i < blocks; i++) {
            Memory::io_physical->write(i+beg, pid);
            Memory::used[i+beg] = 1;
        }
    }

    return beg;
}
