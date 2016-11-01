#include <iostream>
#include <cstring>
#include <fstream>

int main () {
    std::streampos size;
    char str[] = "Vai curinthia é nóis.";

    std::fstream file("teste.bin", std::ios::binary|std::ios::out);
    if (file.is_open()) {
        file.seekg(7);
        file.write(str, sizeof(char)*strlen(str));
        file.close();
    } else {
        std::cout << "Faiô!";
    }
}
