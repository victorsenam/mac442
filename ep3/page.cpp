#include "page.h"

std::unordered_map<unsigned, unsigned> Page::table;
Page::Algorithm * Page::manager;

void Page::reinit () {
    Page::table.clear();

    Page::manager->reinit();
}

unsigned Page::get (unsigned virt_position) {
    std::unordered_map<unsigned, unsigned>::iterator it;
    unsigned page = virt_position/Memory::page;
    unsigned offset = virt_position%Memory::page;
    it = table.find(page);

    if (it == table.end()) {
        return map(page)*Memory::page + offset;
    } else {
        return it->second*Memory::page + offset;
    }
}

void Page::visit (unsigned pid, unsigned virt_position, bool converted) {
    unsigned phys_position = virt_position;
    if (!converted)
        phys_position = get(virt_position);

    Memory::io_physical->write(phys_position, pid);
    Page::manager->signal(virt_position/Memory::page);
}

unsigned Page::map (unsigned virt_page) {
    unsigned phys_page = table.size();

    if (phys_page >= Memory::total/Memory::page) {
        unsigned to_remove = manager->page_to_remove();
        unsigned phys_page = table[to_remove];

        update_virt(phys_page, to_remove);
        table.erase(to_remove);
    }

    update_phys(virt_page, phys_page);
    table[virt_page] = phys_page;
    return phys_page;
}

void Page::update_phys (unsigned virt_page, unsigned phys_page) {
    Memory::io_physical->write(phys_page*Memory::page, Memory::io_virtual, virt_page*Memory::page, Memory::page);
}

void Page::update_virt (unsigned phys_page, unsigned virt_page) {
    Memory::io_virtual->write(virt_page*Memory::page, Memory::io_physical, phys_page*Memory::page, Memory::page);
}

void Page::finish () {
    for (auto mapping : table)
        update_virt(mapping.second, mapping.first);
}

void Page::Algorithm::reinit () {
}

unsigned Page::Algorithm::page_to_remove () {
    return 0u;
}

void Page::Algorithm::signal (unsigned virt_page) {
}

