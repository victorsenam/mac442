#include "page_optimal.h"

void PageOptimal::reinit () {
    if (!simulation_mode) {
        event.clear();
        simulation_mode = true;
        Runner::execute(0);
        simulation_mode = false;
    } else {
        for (unsigned i = 0; i < Memory::virt/Memory::page; i++)
            event.push_back(std::queue<long long>());

        current_time = 0;
    }
}

unsigned PageOptimal::page_to_remove () {
    unsigned worst = Memory::virt/Memory::page;
    long long time = -1;
    for (auto mapped : Page::table) {
        while (!event[mapped.first].empty() && event[mapped.first].front() < current_time)
            event[mapped.first].pop();

        if (event[mapped.first].empty()) {
            return mapped.first;
        } else if (event[mapped.first].front() > time) {
            time = event[mapped.first].front();
            worst = mapped.first;
        }
    }

    return worst;
}

void PageOptimal::visit (unsigned pid, unsigned virt_position, bool converted) {
    if (!converted) {
        if (simulation_mode)
            event[virt_position/Memory::page].push(current_time);
        current_time++;
    }

    Page::Algorithm::visit(pid, virt_position, converted);
}
