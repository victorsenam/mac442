#ifndef EP3_BINARY
#define EP3_BINARY

#include <fstream>
#include <string>
#include <cassert>

class BinaryIO {
public: 
    std::fstream file;

    BinaryIO (std::string str);

    void write (unsigned pos, int val);
    int read (unsigned pos);
};

#endif
