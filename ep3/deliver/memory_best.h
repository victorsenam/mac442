/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
// IMPLEMENTS BEST FIT ALGORITHM
#ifndef EP3_MEMORY_BEST
#define EP3_MEMORY_BEST

#include "memory.h"

class MemoryBest : public Memory::Algorithm {
    virtual unsigned find_free_space (unsigned blocks);
};

#endif
