#include "helper.h"

void Helper::assert (bool expression, std::string message) {
    if (!expression) {
        std::cout << message << std::endl;
        exit(1);
    }
}
