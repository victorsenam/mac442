#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include "trace.h"

std::string split (std::string & a, char sep) {
    int pos = a.find(sep);
    int n = a.length();
    std::string ret = a.substr(0, pos);
    a = a.substr(pos+1, n-pos-1);
    return ret;
}

int main (int argc, char * argv[]) {
    while (true) {
        std::string line = readline("(ep3): ");

        if (line == "sai")
            break;

        add_history(line.c_str());

        std::string command = split(line, ' ');

        std::cout << command << std::endl;
        std::cout << line << std::endl;
    }
}
