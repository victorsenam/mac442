#include "page.h"

std::map<unsigned, unsigned> Page::table;
Page::Algorithm * Page::manager;

unsigned Page::get_page (unsigned block) {
    return block/(Memory::page/Memory::block);
}

void Page::reinit () {
    Page::table.clear();
}

void Page::Algorithm::visit (unsigned page) {
    return;
}


