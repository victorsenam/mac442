/* Nathan Benedetto Proença 8941276  **
** Victor Sena Molero 8941317        */
#include "helper.h"

void Helper::assure (bool expression, std::string message) {
    if (!expression) {
        std::cout << message << std::endl;
        abort();
    }
}
