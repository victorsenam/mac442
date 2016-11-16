#ifndef EP3_PAGE
#define EP3_PAGE

#include "memory.h"
#include <vector>

class Page {
public:
    class Algorithm;

    static Algorithm * manager;

    static unsigned get_page (unsigned block);
};

class Page::Algorithm {
public:
    virtual void visit (unsigned page);
};

#endif
