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
};

class Memory::Algorithm {
public:
    virtual unsigned allocate (unsigned size);
    virtual void visit (unsigned position);
};

#endif
