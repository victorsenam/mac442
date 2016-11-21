/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "page_clock.h"

void PageClock::reinit () {
    fifo.clear();
    ptr = fifo.end();
}

unsigned PageClock::page_to_remove () {
    while (true) {
        if (ptr == fifo.end())
            ptr = fifo.begin();

        std::pair<unsigned, unsigned> to_remove = *ptr;

        if (Page::r[to_remove.second]) {
            Page::r[to_remove.second] = 0;
            ++ptr;
        } else {
            ptr = fifo.erase(ptr);
            return to_remove.first;
        }

    }
}

void PageClock::add (unsigned virt_page, unsigned phys_page) {
    fifo.insert(ptr, std::pair<unsigned, unsigned>(virt_page, phys_page));
    Page::r[phys_page] = 1;
}
