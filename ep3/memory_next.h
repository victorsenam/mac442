/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
// IMPLEMENTS NEXT FIT ALGORITHM
#ifndef EP3_MEMORY_NEXT
#define EP3_MEMORY_NEXT

#include "memory.h"

class MemoryNext : public Memory::Algorithm {
    unsigned last;

    virtual void reinit ();
    virtual unsigned find_free_space (unsigned blocks);
};

#endif
