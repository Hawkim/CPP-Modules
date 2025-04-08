#include "Fixed.hpp"
#include <cmath>

// Constructors and Destructor
Fixed::Fixed() : value(0) {
    // std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int value) : value(value << _fractionalBits) {
    // std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float value) : value(roundf(value * (1 << _fractionalBits))) {
    // std::cout << "Float constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& other) : value(other.value) {
    // std::cout << "Copy constructor called" << std::endl;
}

Fixed& Fixed::operator=(const Fixed& other) {
    // std::cout << "Copy assignment operator called" << std::endl;
    if (this != &other)
        value = other.value;
    return *this;
}

Fixed::~Fixed() {
    // std::cout << "Destructor called" << std::endl;
}

// Basic member functions
int Fixed::getRawBits() const {
    return value;
}

void Fixed::setRawBits(int const raw) {
    value = raw;
}

float Fixed::toFloat() const {
    return static_cast<float>(value) / (1 << _fractionalBits);
}

int Fixed::toInt() const {
    return value >> _fractionalBits;
}

// Comparison operators
bool Fixed::operator>(const Fixed& other) const { return value > other.value; }
bool Fixed::operator<(const Fixed& other) const { return value < other.value; }
bool Fixed::operator>=(const Fixed& other) const { return value >= other.value; }
bool Fixed::operator<=(const Fixed& other) const { return value <= other.value; }
bool Fixed::operator==(const Fixed& other) const { return value == other.value; }
bool Fixed::operator!=(const Fixed& other) const { return value != other.value; }

Fixed Fixed::operator+(const Fixed& other) const {
    return Fixed(this->toFloat() + other.toFloat());
}

Fixed Fixed::operator-(const Fixed& other) const {
    return Fixed(this->toFloat() - other.toFloat());
}

Fixed Fixed::operator*(const Fixed& other) const {
    // Correct fixed-point multiplication
    long long product = static_cast<long long>(value) * static_cast<long long>(other.value);
    return Fixed(static_cast<float>(product) / (1 << (_fractionalBits * 2)));
}

Fixed Fixed::operator/(const Fixed& other) const {
    if (other.value == 0) {
        std::cerr << "Error: Division by zero" << std::endl;
        exit(EXIT_FAILURE);
    }
    // Correct fixed-point division
    long long dividend = static_cast<long long>(value) << _fractionalBits;
    return Fixed(static_cast<float>(dividend) / other.value);
}

// Increment/decrement operators
Fixed& Fixed::operator++() {
    value += 1;
    return *this;
}

Fixed Fixed::operator++(int) {
    Fixed temp(*this);
    value += 1;
    return temp;
}

Fixed& Fixed::operator--() {
    value -= 1;
    return *this;
}

Fixed Fixed::operator--(int) {
    Fixed temp(*this);
    value -= 1;
    return temp;
}

// Min/max functions
Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a > b) ? a : b;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
    os << fixed.toFloat();
    return os;
}