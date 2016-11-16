#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include "trace.h"
#include "runner.h"

#include "memory.h"
#include "memory_first.h"
#include "memory_next.h"

#include "page.h"


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

    Memory::io_physical = new BinaryIO("/tmp/ep3.mem");
    Memory::io_virtual = new BinaryIO("/tmp/ep3.vir");

    while (true) {
        std::string line = readline("(ep3): ");

        if (line == "sai")
            break;

        add_history(line.c_str());

        std::string command = split(line, ' ');

        if (command == "carrega") {
            Trace::read(line);
        } else if (command == "espaco") {
            if (line == "1")
                Memory::manager = new MemoryFirst();
            else if (line == "2")
                Memory::manager = new MemoryNext();
            else
                std::cout << "Gerenciador de Memória Desconhecido\n";
		} else if (command == "substitui") {
        } else if (command == "executa") {
            Runner::execute(stoul(line, nullptr, 10));
        } else {
            std::cout << "Comando Desconhecido\n";
        }
            
    }
}
