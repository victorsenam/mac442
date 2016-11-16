#include "memory_next.h"

unsigned MemoryNext::find_free_space (unsigned blocks) {
    unsigned ls = last;
    
    for (unsigned i = last; i < Memory::used.size(); i++) {
        if (Memory::used[i]) ls = i+1;
        else if (ls - i + 1 >= blocks) {
            last = i;
            return ls;
        }
    }

    if (!last) return Memory::used.size();

    last = 0;
    return MemoryNext::find_free_space(blocks);
}

void MemoryNext::reinit () {
    last = 0;
}
