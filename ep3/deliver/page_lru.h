/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
// IMPLEMENTS LRU PAGE SUBSTITUTION ALGORITHM (4th version)
#ifndef EP3_PAGE_LRU
#define EP3_PAGE_LRU

#include <list>
#include <climits>

#include "page.h"

class PageLRU : public Page::Algorithm {
public:
    void reinit ();
    unsigned page_to_remove ();
    
    void signal ();

private:
    std::vector<unsigned long long> p;
};

#endif
