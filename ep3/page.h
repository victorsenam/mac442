#ifndef EP3_PAGE
#define EP3_PAGE

#include "memory.h"
#include <vector>
#include <map>

class Page {
public:
    class Algorithm;

    static Algorithm * manager;

    static std::map<unsigned, unsigned> table;

    static unsigned get_page (unsigned block);
    static void reinit ();
};

class Page::Algorithm {
public:
    virtual void visit (unsigned page);
};

#endif
