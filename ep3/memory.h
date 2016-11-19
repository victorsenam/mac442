#ifndef EP3_MEMORY
#define EP3_MEMORY

#include <vector>
#include "binaryio.h"
#include "helper.h"
#include "process.h"
#include "page.h"

class Page;
class Memory {
public:
    class Algorithm;

    static unsigned int total,
                        virt,
                        block,
                        page;

    static Algorithm * manager;

    // one position per byte
    // each byte is represented by 4 bytes in these files (so that we can write each process' pid)
    // each byte has -1 written on it (if it's unused) or a process pid (if it's used)
    static BinaryIO * io_physical;
    static BinaryIO * io_virtual;

    // one position (bool, occupies one bit) per block (Memory::block bytes)
    // refers to io_virtual file
    // if bit is set, block is assigned to some process
    // if bit is not set, block is free
    static std::vector<bool> used;

    static void reinit ();
};

class Memory::Algorithm {
public:
    // this changes for each algorithm
    virtual unsigned find_free_space (unsigned blocks);
    virtual void reinit ();

    void visit (unsigned pid, unsigned position);
    void free (unsigned initial_block, unsigned blocks);
    void reserve (Process & proc, unsigned blocks, unsigned begin);
};

#endif
