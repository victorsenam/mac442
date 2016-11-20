#include "page.h"
#include <ctime>

std::unordered_map<unsigned, unsigned> Page::table;
std::vector<bool> Page::r;
Page::Algorithm * Page::manager;
unsigned Page::faults;

void Page::reinit () {
    Page::manager->reinit();

    Page::table.clear();
    Page::faults = 0;

    Page::r.clear();
    Page::r.resize(Memory::total/Memory::page, 0);
}

unsigned Page::get (unsigned virt_position) {
    std::unordered_map<unsigned, unsigned>::iterator it;
    unsigned page = virt_position/Memory::page;
    unsigned offset = virt_position%Memory::page;
    it = table.find(page);

    if (it == table.end()) {
        Page::faults++;
        return map(page)*Memory::page + offset;
    } else {
        return it->second*Memory::page + offset;
    }
}

void Page::Algorithm::visit (unsigned pid, unsigned virt_position, bool converted) {
    unsigned phys_position = virt_position;
    if (!converted)
        phys_position = get(virt_position);

    Memory::io_physical->write(phys_position, pid);
}

unsigned Page::map (unsigned virt_page) {
    unsigned phys_page = table.size();

    if (phys_page >= Memory::total/Memory::page) {
        unsigned to_remove = manager->page_to_remove();
        phys_page = table[to_remove];

        update_virt(phys_page, to_remove);
        table.erase(to_remove);
    }

    Page::manager->add(virt_page, phys_page);
    update_phys(virt_page, phys_page);
    table[virt_page] = phys_page;
    r[phys_page] = 1;
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

void Page::reset_r () {
    for (auto mapping : table)
        r[mapping.second] = 0;
}

void Page::Algorithm::reinit () {
}

unsigned Page::Algorithm::page_to_remove () {
    return 0u;
}

void Page::Algorithm::signal () {
}

void Page::Algorithm::add (unsigned virt_page, unsigned phys_page) {
    Page::r[phys_page] = 1;
}
