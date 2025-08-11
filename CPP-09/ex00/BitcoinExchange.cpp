#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <cctype>
#include <cstdlib>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

static bool isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

std::string BitcoinExchange::trim(const std::string& s) {
    std::string::size_type a = 0, b = s.size();
    while (a < b && std::isspace(static_cast<unsigned char>(s[a]))) ++a;
    while (b > a && std::isspace(static_cast<unsigned char>(s[b - 1]))) --b;
    return s.substr(a, b - a);
}

bool BitcoinExchange::startsWith(const std::string& s, const std::string& p) {
    return s.size() >= p.size() && s.compare(0, p.size(), p) == 0;
}

bool BitcoinExchange::isAllDigits(const std::string& s) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); ++i)
        if (!std::isdigit(static_cast<unsigned char>(s[i]))) return false;
    return true;
}

bool BitcoinExchange::looksLikeDate(const std::string& s) {
    if (s.size() != 10)
     return false;                // YYYY-MM-DD
    return std::isdigit(s[0]) && std::isdigit(s[1]) && std::isdigit(s[2]) && std::isdigit(s[3]) &&
           s[4] == '-' &&
           std::isdigit(s[5]) && std::isdigit(s[6]) &&
           s[7] == '-' &&
           std::isdigit(s[8]) && std::isdigit(s[9]);
}

bool BitcoinExchange::parseDate(const std::string& s, int& y, int& m, int& d) {
    if (!looksLikeDate(s)) return false;
    y = std::atoi(s.substr(0,4).c_str());
    m = std::atoi(s.substr(5,2).c_str());
    d = std::atoi(s.substr(8,2).c_str());
    return isValidDateYMD(y, m, d);
}

bool BitcoinExchange::isValidDateYMD(int y, int m, int d) {
    if (m < 1 || m > 12) return false;
    if (d < 1) return false;
    static const int mdays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int days = mdays[m-1];
    if (m == 2 && isLeap(y)) days = 29;
    return d <= days;
}

bool BitcoinExchange::parseNumber(const std::string& s, double& out) {
    // valid: positive integer or float (no leading '+' per common solutions)
    std::istringstream iss(s);
    double v;
    iss >> v;
    if (!iss || !iss.eof()) return false;
    out = v;
    return true;
}

void BitcoinExchange::loadDatabase(const std::string& csvPath) {
    std::ifstream f(csvPath.c_str());
    if (!f) throw std::runtime_error("Error: could not open database.");

    std::string line;
    // optional header "date,exchange_rate"
    if (std::getline(f, line)) {
        std::string t = trim(line);
        if (!startsWith(t, "date")) {
            // first line might already be data, handle below by processing it after rewinding via stringstream
            std::istringstream first(line);
            // fallthrough by reusing parsing loop with the already-read line
            // easiest: process via a small loop that starts with t!=header
            // but we’ll just handle in the while-loop below by keeping 'line' as already read.
            // So we process 'line' first, then continue with rest.
            // To do that, we’ll parse it here and then proceed with the usual while loop.
            // If it fails, we just ignore; DB rows can be many.
            std::string date, priceStr;
            std::string::size_type comma = line.find(',');
            if (comma != std::string::npos) {
                date = trim(line.substr(0, comma));
                priceStr = trim(line.substr(comma + 1));
                int y,m,d;
                if (parseDate(date, y, m, d)) {
                    double price;
                    if (parseNumber(priceStr, price))
                        _rateByDate[date] = price;
                }
            }
        }
    }

    while (std::getline(f, line)) {
        std::string t = trim(line);
        if (t.empty()) continue;
        if (startsWith(t, "date")) continue;

        std::string::size_type comma = t.find(',');
        if (comma == std::string::npos) continue;

        std::string date = trim(t.substr(0, comma));
        std::string priceStr = trim(t.substr(comma + 1));

        int y, m, d;
        if (!parseDate(date, y, m, d)) continue;

        double price;
        if (!parseNumber(priceStr, price)) continue;

        _rateByDate[date] = price;
    }

    if (_rateByDate.empty())
        throw std::runtime_error("Error: empty or invalid database.");
}

bool BitcoinExchange::getRateOnOrBefore(const std::string& date, double& rate) const {
    if (_rateByDate.empty()) return false;
    std::map<std::string,double>::const_iterator it = _rateByDate.lower_bound(date);
    if (it != _rateByDate.end() && it->first == date) { // exact
        rate = it->second;
        return true;
    }
    if (it == _rateByDate.begin()) return false; // no lower date
    --it; // closest lower date
    rate = it->second;
    return true;
}

void BitcoinExchange::processInputFile(const std::string& inputPath) const {
    std::ifstream in(inputPath.c_str());
    if (!in) throw std::runtime_error("Error: could not open file.");

    std::string line;
    while (std::getline(in, line)) {
        std::string t = trim(line);
        if (t.empty()) continue;
        if (startsWith(t, "date")) continue; // skip header

        // Expect "date | value"
        std::string::size_type bar = t.find('|');
        if (bar == std::string::npos) {
            std::cout << "Error: bad input => " << t << std::endl;
            continue;
        }

        std::string date = trim(t.substr(0, bar));
        std::string valueStr = trim(t.substr(bar + 1));

        // Basic shape checks
        if (!looksLikeDate(date)) {
            std::cout << "Error: bad input => " << t << std::endl;
            continue;
        }

        int y,m,d;
        if (!parseDate(date, y, m, d)) {
            std::cout << "Error: bad input => " << t << std::endl;
            continue;
        }

        double value;
        if (!parseNumber(valueStr, value)) {
            std::cout << "Error: bad input => " << t << std::endl;
            continue;
        }

        if (value < 0.0) {
            std::cout << "Error: not a positive number." << std::endl;
            continue;
        }
        if (value > 1000.0) {
            std::cout << "Error: too large a number." << std::endl;
            continue;
        }

        double rate;
        if (!getRateOnOrBefore(date, rate)) {
            std::cout << "Error: bad input => " << t << std::endl; // or a custom message if you prefer
            continue;
        }

        double result = value * rate;
        // match subject format: "YYYY-MM-DD => value = result"
        std::cout << date << " => " << value << " = " << result << std::endl;
    }
}
