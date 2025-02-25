#include "StringReplacer.hpp"
#include <iostream>

int main(int argc, char** av) {
    if (argc != 4) {
        std::cerr << "Incorrect usage: " << av[0] << " <filename> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];

    StringReplacer replacer(filename, s1, s2);
    if (!replacer.replaceAndSave()) {
        return 1;
    }

    std::cout << "Replacement completed successfully. Check " << filename << ".replace" << std::endl;
    return 0;
}