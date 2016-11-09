#ifndef EP3_MEMORY
#define EP3_MEMORY

#include <vector>
#include <iostream>

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
    virtual void respond();
};

#endif
