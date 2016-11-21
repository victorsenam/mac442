/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "binaryio.h"
#include <bitset>

BinaryIO::BinaryIO (std::string str) {
    std::fstream(str.c_str(), std::ios::out);
    file = std::fstream(str.c_str(), std::ios::binary|std::ios::out|std::ios::in);

    assert(file.is_open());
}

void BinaryIO::write (unsigned pos, BinaryIO * source, unsigned begin, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        unsigned val = source->read(begin+i);
        write(pos + i, val);
    }
}

void BinaryIO::write (unsigned pos, int val) {
    char buff[4];

    pos *= 4;
    
    for (int i = 3; i >= 0; i--) {
        buff[i] = (val&((1u<<8)-1));
        val >>= 8;
    }

    file.seekg(pos);
    file.write(buff, 4);
    file.flush();
}

int BinaryIO::read (unsigned pos) {
    unsigned val = 0;
    char buff[4];

    pos *= 4;

    file.seekg(pos);
    file.read(buff, 4);

    for (int i = 0; i < 4; i++) {
        val <<= 8;
        val |= (unsigned(buff[i])&((1u<<8)-1));
    }
    return val;
}
