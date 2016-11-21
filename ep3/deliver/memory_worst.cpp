/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "memory_worst.h"

unsigned MemoryWorst::find_free_space (unsigned blocks) {
    unsigned best_start = Memory::used.size();
    unsigned best_size = 0;
    unsigned ls = 0;
    
    for (unsigned i = 0; i <= Memory::used.size(); i++) {
        if (i == Memory::used.size() || Memory::used[i]) {
            if (i - ls >= blocks && (i - ls > best_size || best_start == Memory::used.size())) {
                best_size = i - ls;
                best_start = ls;
            }
            ls = i+1;
        }
    }

    return best_start;
}
