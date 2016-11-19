#ifndef EP3_PAGE
#define EP3_PAGE

#include "memory.h"
#include <vector>
#include <unordered_map>
#include <iostream>

class Memory;
class Page {
public:
    class Algorithm;

    static Algorithm * manager;
    static std::unordered_map<unsigned, unsigned> table;

    // receive positions from virtual memory
    static unsigned get (unsigned virt_position);
    static void reinit ();

    static void finish ();

private:
    // receive pages from virtual memory
    static unsigned map (unsigned virt_page);
    
    static void update_phys (unsigned virt_page, unsigned phys_page);
    static void update_virt (unsigned phys_page, unsigned virt_page);
};

class Page::Algorithm {
public:
    virtual void reinit ();
    virtual unsigned page_to_remove ();
    virtual void signal (unsigned virt_page);

    virtual void visit (unsigned pid, unsigned virt_position, bool converted=false);
};

#endif
