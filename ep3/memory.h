#ifndef EP3_MEMORY
#define EP3_MEMORY

#include <vector>

class Memory {
public:
    class Algorithm;

    static unsigned int total,
                        virt,
                        block,
                        page;

    static Algorithm * manager;

    static std::vector<bool> used;

    static void reinit ();
};

class Memory::Algorithm {
public:
    virtual unsigned allocate (unsigned pid, unsigned blocks);
    virtual void visit (unsigned block);
    virtual void free (unsigned initial_block, unsigned blocks);
};

#endif
