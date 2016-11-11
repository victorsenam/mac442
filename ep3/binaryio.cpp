#include "binaryio.h"

BinaryIO::BinaryIO (std::string str) {
    file = std::fstream(str.c_str(), std::ios::binary|std::ios::out|std::ios::in);

    std::cout << str << std::endl;
    assert(file.is_open());
}

void BinaryIO::write (unsigned pos, int val) {
    char buff[4];

    pos *= 4;
    
    for (int i = 3; i >= 0; i--) {
        buff[i] = (val&((1<<8)-1));
        val >>= 8;
    }

    file.seekg(pos);
    file.write(buff, 4);
    file.flush();
}

int BinaryIO::read (unsigned pos) {
    int val = 0;
    char buff[4];

    pos *= 4;

    file.seekg(pos);
    file.read(buff, 4);

    for (int i = 0; i < 4; i++) {
        val <<= 8;
        val |= buff[i];
    }
    return val;
}

int BinaryIO::main () {
    char c;
    unsigned p;
    int v;
    std::string fname;

    std::cin >> fname;

    BinaryIO obj(fname);

    while (scanf(" %c %u", &c, &p) != EOF) {
        if (c == 'w') {
            scanf("%d", &v);
            obj.write(p, v);
        } else {
            printf("%d\n", obj.read(p));
        }
    }

    return 0;
}
