#include "page.h"

Page::Algorithm * Page::manager;

void Page::Algorithm::respond() {
    std::cout << "Page Ok!" << std::endl;
}
