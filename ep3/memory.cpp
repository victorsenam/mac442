#include "memory.h"

unsigned int Memory::total, 
			 Memory::virt,
			 Memory::block, 
			 Memory::page;
std::vector<bool> Memory::used;
Memory::Algorithm * Memory::manager;


void Memory::reinit () {
	Memory::used.clear();
	Memory::used.resize(Memory::total/Memory::block, 0);
}

unsigned Memory::Algorithm::allocate (unsigned pid, unsigned size) {
    return 0u;
}

void Memory::Algorithm::visit (unsigned position) {
    return;
}

void Memory::Algorithm::free (unsigned position, unsigned size) {
    return;
}
