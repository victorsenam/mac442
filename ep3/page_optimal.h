// IMPLEMENTS OPTIMAL PAGE SUBSTITUTION ALGORITHM
#ifndef EP3_PAGE_OPTIMAL
#define EP3_PAGE_OPTIMAL

#include "page.h"
#include <vector>
#include <queue>
#include "runner.h"
#include "task.h"
#include "process.h"

class PageOptimal : public Page::Algorithm {
public:
    void reinit ();
    unsigned page_to_remove ();

    void visit (unsigned pid, unsigned virt_position, bool converted=false);

private:
    std::vector<std::queue<long long> > event;
    bool simulation_mode;
    long long current_time;
};

#endif
