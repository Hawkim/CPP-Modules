#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
public:
    BitcoinExchange();
    ~BitcoinExchange();

    // Load "date,price" CSV 
    void loadDatabase(const std::string& csvPath);

    // Process "date | value" input file and print results/errors to std::cout.
    // Throws std::runtime_error if the input file can't be opened.
    void processInputFile(const std::string& inputPath) const;

private:
    std::map<std::string, double> _rateByDate; // key: "YYYY-MM-DD"

    static std::string trim(const std::string& s);
    static bool isAllDigits(const std::string& s);
    static bool parseDate(const std::string& s, int& y, int& m, int& d);
    static bool isValidDateYMD(int y, int m, int d);
    static bool parseNumber(const std::string& s, double& out); // int or float
    static bool startsWith(const std::string& s, const std::string& prefix);

    // Returns true if s looks like "YYYY-MM-DD"
    static bool looksLikeDate(const std::string& s);

    // Find rate for date or closest lower date; returns false if none (date before DB start).
    bool getRateOnOrBefore(const std::string& date, double& rate) const;
};

#endif
