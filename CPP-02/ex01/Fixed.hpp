#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
private:
    int value;
    static const int _fractionalBits = 8;

public:
    Fixed();                                // Default constructor
    Fixed(const int value);                 // Int constructor
    Fixed(const float value);               // Float constructor
    Fixed(const Fixed& other);              // Copy constructor
    Fixed& operator=(const Fixed& other);   // Copy assignment operator
    ~Fixed();                              // Destructor

    int getRawBits() const;
    void setRawBits(int const raw);

    float toFloat() const;
    int toInt() const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif