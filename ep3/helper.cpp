#include "helper.h"

void Helper::assure (bool expression, std::string message) {
    if (!expression) {
        std::cout << message << std::endl;
        exit(1);
    }
}
