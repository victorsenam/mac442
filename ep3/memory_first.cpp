/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "memory_first.h"

unsigned MemoryFirst::find_free_space (unsigned blocks) {
    unsigned ls = 0;
    
    for (unsigned i = 0; i < Memory::used.size(); i++) {
        if (Memory::used[i]) ls = i+1;
        else if (ls - i + 1 >= blocks)
            return ls;
    }

    return Memory::used.size();
}
