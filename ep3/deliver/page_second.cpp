/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "page_second.h"

void PageSecond::reinit () {
    while (!fifo.empty())
        fifo.pop();
}

unsigned PageSecond::page_to_remove () {
    while (true) {
        std::pair<unsigned, unsigned> to_remove = fifo.front();
        fifo.pop();
        if (Page::r[to_remove.second]) {
            Page::r[to_remove.second] = 0;
            fifo.push(to_remove);
        } else {
            return to_remove.first;
        }
    }
}

void PageSecond::add (unsigned virt_page, unsigned phys_page) {
    fifo.push(std::pair<unsigned, unsigned>(virt_page, phys_page));
    Page::r[phys_page] = 1;
}
