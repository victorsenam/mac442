#include "memory.h"

unsigned int Memory::total, 
			 Memory::virt,
			 Memory::block, 
			 Memory::page;

Memory::Algorithm * Memory::manager;

void Memory::Algorithm::respond() {
    std::cout << "Memory Ok!" << std::endl;
}
