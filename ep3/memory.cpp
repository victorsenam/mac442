#include "memory.h"

unsigned int Memory::total, 
			 Memory::virt,
			 Memory::block, 
			 Memory::page;
std::vector<bool> Memory::used;
Memory::Algorithm * Memory::manager;
float Memory::elapsed_time;

BinaryIO * Memory::io_physical;
BinaryIO * Memory::io_virtual;

void Memory::reinit () {
	Memory::used.clear();
	Memory::used.resize(Memory::virt/Memory::block, 0);

    Memory::elapsed_time = 0.;

	for (unsigned i = 0; i < Memory::total; i++)
		Memory::io_physical->write(i, -1);
	
	for (unsigned i = 0; i < Memory::virt; i++)
		Memory::io_virtual->write(i, -1);

    Memory::manager->reinit();
}

void Memory::reserve (Process & proc, unsigned blocks, unsigned begin) {
    proc.first_block = begin;
    unsigned pid = proc.id;

    Helper::assure(begin+blocks <= Memory::used.size(), "Tentando reservar bloco não acessível (não há memória suficiente)\n");


    for (unsigned i = 0; i < blocks; i++) {
        unsigned phys_pos = Page::get((begin+i)*Memory::block);
        Memory::used[begin+i] = 1;
        for (unsigned j = 0; j < Memory::block; j++) {
            Page::manager->visit(pid, phys_pos+j, true);
        }
    }
}

void Memory::free (unsigned initial_block, unsigned blocks) {
	for (unsigned i = 0; i < blocks; i++) {
        unsigned phys_pos = Page::get((initial_block+i)*Memory::block);
        used[i+initial_block] = 0;
        for (unsigned j = 0; j < Memory::block; j++)
            Page::manager->visit(-1, phys_pos+j, true);
    }
}

unsigned Memory::Algorithm::find_free_space (unsigned blocks) {
    Helper::assure(false, "Você não carregou nenhum algoritmo de Gerenciamento de Memória\n");
    return 0u;
}

void Memory::Algorithm::reinit () {
    return;

}
