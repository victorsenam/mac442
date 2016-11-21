/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
// IMPLEMENTS CLOCK PAGE SUBSTITUTION ALGORITHM
#ifndef EP3_PAGE_CLOCK
#define EP3_PAGE_CLOCK

#include <list>

#include "page.h"

class PageClock : public Page::Algorithm {
public:
    void reinit ();
    unsigned page_to_remove ();
    void add (unsigned virt_page, unsigned phys_page);

private:
    std::list<std::pair<unsigned, unsigned> > fifo;
    std::list<std::pair<unsigned, unsigned> >::iterator ptr;
};

#endif
