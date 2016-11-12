#include "memory.h"

unsigned int Memory::total, 
			 Memory::virt,
			 Memory::block, 
			 Memory::page;

Memory::Algorithm * Memory::manager;

unsigned Memory::Algorithm::allocate (unsigned size) {
    return 0u;
}

void Memory::Algorithm::visit (unsigned position) {
    return;
}

