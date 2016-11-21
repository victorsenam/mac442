/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
// IMPLEMENTS SECOND CHANCE PAGE SUBSTITUTION ALGORITHM
#ifndef EP3_PAGE_SECOND
#define EP3_PAGE_SECOND

#include <queue>

#include "memory.h"

class PageSecond : public Page::Algorithm {
public:
    void reinit ();
    unsigned page_to_remove ();
    void add (unsigned virt_page, unsigned phys_page);

private:
    std::queue<std::pair<unsigned, unsigned> > fifo;
};

#endif
