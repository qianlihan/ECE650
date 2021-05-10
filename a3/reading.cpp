#include <iostream>
#include <stdlib.h>

int main (int argc, char **argv) {
    while (!std::cin.eof()) {
        std::string line;
        getline(std::cin, line);
        std::cout << line <<std::endl;
    }
    return 0;
}