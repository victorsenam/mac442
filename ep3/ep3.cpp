#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include "trace.h"

std::string split (std::string & a, char sep) {
    int pos = a.find(sep);
    std::string ret = a.substr(0, pos);
    if (pos == -1)
        a = "";
    else
        a = a.substr(pos+1);
    return ret;
}

int main (int argc, char * argv[]) {
    Memory::manager = new Memory::Algorithm();
	Page::manager = new Page::Algorithm();

    while (true) {
        std::string line = readline("(ep3): ");

        if (line == "sai")
            break;

        add_history(line.c_str());

        std::string command = split(line, ' ');

        if (command == "carrega") {
            Trace::read(line);
        } else if (command == "espaco") {
		} else if (command == "substitui") {
        } else if (command == "executa") {
            Memory::manager->respond();
			Page::manager->responde();
        } else {
            std::cout << "Comando Desconhecido\n";
        }
            
    }
}
