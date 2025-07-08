#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>

// Helper function for converting a string to a float using istringstream.
// Returns true if conversion succeeded; false otherwise.
static bool stringToFloat(const std::string &s, float &result)
{
    std::istringstream iss(s);
    iss >> result;
    // Check if extraction failed or extra characters remain.
    return !(iss.fail() || !iss.eof());
}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
    loadDatabase(databaseFile);
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string &databaseFile)
{
    std::ifstream file(databaseFile.c_str());

    if (!file.is_open())
        throw std::runtime_error("Error: could not open database file.");

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string date, rateStr;

        if (std::getline(iss, date, ',') && std::getline(iss, rateStr))
        {
            float rate;

            if (!stringToFloat(rateStr, rate))
                continue; // Skip invalid lines

            _database[date] = rate;
        }
    }
    file.close();
}

std::string BitcoinExchange::trim(const std::string &s) const
{
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");

    if (start == std::string::npos || end == std::string::npos)
        return "";

    return s.substr(start, end - start + 1);
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.size() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-')
        return false;

    return true;
}

bool BitcoinExchange::isValidValue(const std::string &valueStr, float &value) const
{
    // Only check if conversion succeeds.
    return stringToFloat(valueStr, value);
}

float BitcoinExchange::getExchangeRate(const std::string &date) const
{
    std::map<std::string, float>::const_iterator it = _database.find(date);

    if (it != _database.end())
        return it->second;

    // Use lower_bound to find the first element not less than the given date.
    it = _database.lower_bound(date);
    // If the found date is greater than the input date, move one step back.
    if (it == _database.begin() && it->first > date)
        throw std::runtime_error("Error: date out of range.");

    if (it == _database.end() || it->first > date)
    {
        --it;
        return it->second;
    }

    return it->second;
}

void BitcoinExchange::processInputFile(const std::string &inputFile) const
{
    std::ifstream file(inputFile.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    // Read and discard the header line (if any)
    std::getline(file, line);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string datePart, valuePart;

        if (!std::getline(iss, datePart, '|') || !std::getline(iss, valuePart))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        // Trim the date and value parts
        std::string date = trim(datePart);
        std::string valueStr = trim(valuePart);

        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }

        float value = 0;
        if (!isValidValue(valueStr, value))
        {
            std::cerr << "Error: bad input => " << valueStr << std::endl;
            continue;
        }
        if (value < 0)
        {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000)
        {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        try {
            float rate = getExchangeRate(date);
            float result = value * rate;
            std::cout << date << " => " << value << " = " << result << std::endl;
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
    file.close();
}