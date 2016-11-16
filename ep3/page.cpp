#include "page.h"

unsigned Page::get_page (unsigned block) {
    return block/(Memory::page/Memory::block);
}

Page::Algorithm * Page::manager;

void Page::Algorithm::visit (unsigned page) {
    return;
}

