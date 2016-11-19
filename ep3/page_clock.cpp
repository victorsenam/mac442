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
        ++ptr;

        if (Page::r[to_remove.second]) {
            Page::r[to_remove.second] = 0;
            fifo.insert(ptr, to_remove);
        } else {
            return to_remove.first;
        }
    }
}

void PageClock::add (unsigned virt_page, unsigned phys_page) {
    fifo.insert(ptr, std::pair<unsigned, unsigned>(virt_page, phys_page));
    Page::r[phys_page] = 1;
}
