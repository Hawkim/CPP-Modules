#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    const char* inputPath = argv[1];
    const char* dbPath = (argc == 3) ? argv[2] : "data.csv";

    try {
        BitcoinExchange btc;
        btc.loadDatabase(dbPath);
        btc.processInputFile(inputPath);
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
