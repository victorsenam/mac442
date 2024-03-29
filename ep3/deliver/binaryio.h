/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#ifndef EP3_BINARY
#define EP3_BINARY

#include <fstream>
#include <string>
#include <cassert>

class BinaryIO {
public: 
    std::fstream file;

    BinaryIO (std::string str);

    void write (unsigned pos, BinaryIO * source, unsigned begin, unsigned size);
    void write (unsigned pos, int val);
    int read (unsigned pos);
};

#endif
