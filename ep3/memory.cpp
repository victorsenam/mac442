#include "memory.h"

unsigned int Memory::total, 
			 Memory::virt,
			 Memory::block, 
			 Memory::page;
std::vector<bool> Memory::used;
Memory::Algorithm * Memory::manager;
BinaryIO * Memory::io_physical;
BinaryIO * Memory::io_virtual;

void Memory::reinit () {
	Memory::used.clear();
	Memory::used.resize(Memory::total/Memory::block, 0);

	for (unsigned i = 0; i < Memory::total/Memory::block; i++)
		Memory::io_physical->write(i, -1);
	
	for (unsigned i = 0; i < Memory::virt/Memory::block; i++)
		Memory::io_virtual->write(i, -1);
}

unsigned Memory::Algorithm::allocate (unsigned pid, unsigned size) {
    return 0u;
}

void Memory::Algorithm::visit (unsigned pid, unsigned position) {
	Memory::io_physical->write(position, pid);
}

void Memory::Algorithm::free (unsigned position, unsigned size) {
    return;
}
