#ifndef EP3_MEMORY
#define EP3_MEMORY

#include <vector>

std::vector<bool> memory_free;

unsigned int memory_total, 
             memory_virtual, 
             memory_block, 
             memory_page;

#endif
