#include "ScalarConverter.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <limits>

void ScalarConverter::convert(const std::string& literal) {
    // Handle special cases (nan, inf)
    if (literal == "nan" || literal == "nanf") {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: nanf\n";
        std::cout << "double: nan\n";
        return;
    }
    if (literal == "+inf" || literal == "+inff" || literal == "inf" || literal == "inff") {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: +inff\n";
        std::cout << "double: +inf\n";
        return;
    }
    if (literal == "-inf" || literal == "-inff") {
        std::cout << "char: impossible\n";
        std::cout << "int: impossible\n";
        std::cout << "float: -inff\n";
        std::cout << "double: -inf\n";
        return;
    }

    // Try to convert to double (handles most cases)
    char* endPtr;
    double d = strtod(literal.c_str(), &endPtr);
    bool isChar = (literal.size() == 1 && !isdigit(literal[0]));

    // CHAR conversion
    if (isChar) {
        char c = literal[0];
        std::cout << "char: '" << c << "'\n";
        std::cout << "int: " << static_cast<int>(c) << "\n";
        std::cout << "float: " << static_cast<float>(c) << ".0f\n";
        std::cout << "double: " << static_cast<double>(c) << ".0\n";
        return;
    }

    // Check if conversion was successful
    if (endPtr == literal.c_str() && !isChar) {
        std::cout << "Invalid input\n";
        return;
    }

    // CHAR
    if (d < std::numeric_limits<char>::min() || d > std::numeric_limits<char>::max() ){
        std::cout << "char: impossible\n";
    } else if (!isprint(static_cast<char>(d))) {
        std::cout << "char: Non displayable\n";
    } else {
        std::cout << "char: '" << static_cast<char>(d) << "'\n";
    }

    // INT
    if (d < std::numeric_limits<int>::min() || d > std::numeric_limits<int>::max() || std::isnan(d)) {
        std::cout << "int: impossible\n";
    } else {
        std::cout << "int: " << static_cast<int>(d) << "\n";
    }

    // FLOAT
    float f = static_cast<float>(d);
    if (std::isinf(f) || std::isnan(f)) {
        std::cout << "float: " << f;
        (f == floorf(f)) ? std::cout << ".0f\n" : std::cout << "f\n";
    } else {
        std::cout << "float: " << f;
        (f == floorf(f)) ? std::cout << ".0f\n" : std::cout << "f\n";
    }

    // DOUBLE
    std::cout << "double: " << d;
    (d == floor(d)) ? std::cout << ".0\n" : std::cout << "\n";
}