#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
    public:
        BitcoinExchange(const std::string &databaseFile);
        ~BitcoinExchange();

        // Process an input file (format: "date | value")
        void processInputFile(const std::string &inputFile) const;

    private:
        std::map<std::string, float> _database;

        // Load the CSV database (assumes header in first line)
        void loadDatabase(const std::string &databaseFile);

        // Get the exchange rate for a given date.
        // If the date isn’t present, returns the closest (lower) date’s rate.
        float getExchangeRate(const std::string &date) const;

        // Simple date validation: checks for format "YYYY-MM-DD"
        bool isValidDate(const std::string &date) const;

        // Checks that the value is a valid float between 0 and 1000.
        bool isValidValue(const std::string &valueStr, float &value) const;

        // Utility: trim whitespace from both ends of a string.
        std::string trim(const std::string &s) const;
};

#endif