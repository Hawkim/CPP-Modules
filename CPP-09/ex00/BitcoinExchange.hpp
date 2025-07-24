#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <exception>

class BitcoinExchange {
private:
    std::map<std::string, float> _exchangeRates;
    
    void loadDatabase(const std::string& filename);
    void processInputLine(const std::string& line);
    bool isValidDate(const std::string& date);
    bool isValidValue(const std::string& valueStr, float& value);
    std::string findClosestDate(const std::string& date);

public:
    BitcoinExchange(const std::string& databaseFile);
    void processInputFile(const std::string& inputFile);
};

#endif
