#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

BitcoinExchange::BitcoinExchange(const std::string& databaseFile) {
    loadDatabase(databaseFile);
}

void BitcoinExchange::loadDatabase(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open database file.");
    }

    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos == std::string::npos) 
        continue;
        
        std::string date = line.substr(0, commaPos);
        std::string rateStr = line.substr(commaPos + 1);
        
        float rate = atof(rateStr.c_str());
        _exchangeRates[date] = rate;
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) {
    if (date.length() != 10) return false;
    if (date[4] != '-' || date[7] != '-') return false;

    int year, month, day;
    char dash1, dash2;
    std::istringstream iss(date);
    iss >> year >> dash1 >> month >> dash2 >> day;
    if (iss.fail() || dash1 != '-' || dash2 != '-') return false;

    if (year < 2009 || year > 2023) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        return false;
    }

    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) {
    char* end;
    value = strtof(valueStr.c_str(), &end);
    if (*end != '\0') return false;
    if (value < 0) return false;
    if (value > 1000) return false;
    return true;
}

std::string BitcoinExchange::findClosestDate(const std::string& date) {
    std::map<std::string, float>::iterator it = _exchangeRates.lower_bound(date);
    
    if (it == _exchangeRates.begin()) {
        return it->first;
    }
    if (it == _exchangeRates.end() || it->first != date) {
        --it;
    }
    return it->first;
}

void BitcoinExchange::processInputLine(const std::string& line) {
    size_t pipePos = line.find('|');
    if (pipePos == std::string::npos) {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }

    std::string date = line.substr(0, pipePos);
    date.erase(0, date.find_first_not_of(" \t"));
    date.erase(date.find_last_not_of(" \t") + 1);

    std::string valueStr = line.substr(pipePos + 1);
    valueStr.erase(0, valueStr.find_first_not_of(" \t"));
    valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

    if (!isValidDate(date)) {
        std::cout << "Error: bad input => " << date << std::endl;
        return;
    }

    float value;
    if (!isValidValue(valueStr, value)) {
        if (value < 0) {
            std::cout << "Error: not a positive number." << std::endl;
        } else if (value > 1000) {
            std::cout << "Error: too large a number." << std::endl;
        } else {
            std::cout << "Error: bad input => " << valueStr << std::endl;
        }
        return;
    }

    std::string closestDate = findClosestDate(date);
    float exchangeRate = _exchangeRates[closestDate];
    float result = value * exchangeRate;

    std::cout << date << " => " << value << " = " << result << std::endl;
}

void BitcoinExchange::processInputFile(const std::string& inputFile) {
    std::ifstream file(inputFile.c_str());
    
    if (!file.is_open()) {
        std::cout << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);
    
    while (std::getline(file, line)) {
        processInputLine(line);
    }
    file.close();
}
