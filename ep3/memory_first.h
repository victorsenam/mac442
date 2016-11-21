/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
// IMPLEMENTS FIRST FIT ALGORITHM
#ifndef EP3_MEMORY_FIRST
#define EP3_MEMORY_FIRST

#include "memory.h"

class MemoryFirst : public Memory::Algorithm {
    virtual unsigned find_free_space (unsigned blocks);
};

#endif
