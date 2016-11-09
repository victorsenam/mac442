#ifndef EP3_PAGE
#define EP3_PAGE

#include <vector>
#include <iostream>

class Page {
public:
    class Algorithm;

    static Algorithm * manager;
};

class Page::Algorithm {
public:
    virtual void respond();
};

#endif
