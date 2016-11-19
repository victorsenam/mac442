#include "page_lru.h"

void PageLRU::reinit () {
    p.clear();
    p.resize(Memory::total/Memory::page, 0);
}

unsigned PageLRU::page_to_remove () {
    std::pair<unsigned, unsigned> to_remove = std::pair<unsigned, unsigned>(0,0);
    unsigned long long cp = ULLONG_MAX;

    for (auto mapping : Page::table) {
        if (p[mapping.second] <= cp) {
            cp = p[mapping.second];
            to_remove = mapping;
        }
    }

    p[to_remove.second] = 0;
    Page::r[to_remove.second] = 0;
    return to_remove.first;
}

void PageLRU::signal () {
    for (auto mapping : Page::table) {
        unsigned long long & att = p[mapping.second];

        att >>= 1;
        if (Page::r[mapping.second])
            att |= (1llu<<63);
    }
}
