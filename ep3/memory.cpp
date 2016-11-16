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

	for (unsigned i = 0; i < Memory::total; i++)
		Memory::io_physical->write(i, -1);
	
	for (unsigned i = 0; i < Memory::virt; i++)
		Memory::io_virtual->write(i, -1);
}

void Memory::Algorithm::reserve (Process & proc, unsigned blocks, unsigned begin) {
    proc.first_block = begin;
    unsigned pid = proc.id;

    Helper::assure(begin+blocks <= Memory::used.size(), "Tentando reservar bloco não acessível (não há memória suficiente)\n");

    for (unsigned i = 0; i < blocks; i++) {
        Memory::used[begin+i] = 1;
        for (unsigned j = 0; j < Memory::block; j++) {
            Memory::io_physical->write((i+begin)*Memory::block + j, pid);
        }
    }
}

void Memory::Algorithm::visit (unsigned pid, unsigned position) {
	Memory::io_physical->write(position, pid);
}

void Memory::Algorithm::free (unsigned initial_block, unsigned blocks) {
	for (unsigned i = 0; i < blocks; i++) {
        used[i+initial_block] = 0;
        for (unsigned j = 0; j < Memory::block; j++) {
            Memory::io_physical->write((i+initial_block)*Memory::block + j, -1);
        }
    }
}

unsigned Memory::Algorithm::find_free_space (unsigned blocks) {
    Helper::assure(false, "Você não carregou nenhum algoritmo de Gerenciamento de Memória\n");
    return 0u;
}
