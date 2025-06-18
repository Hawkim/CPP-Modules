#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stdexcept>
#include <iostream>

template <typename T>
class Array {
private:
    T* _array;
    unsigned int _size;

public:
    // Default constructor (empty array)
    Array() : _array(NULL), _size(0) {}

    // Constructor with size
    explicit Array(unsigned int n) : _array(new T[n]()), _size(n) {}

    // Copy constructor
    Array(const Array& other) : _array(new T[other._size]), _size(other._size) {
        for (unsigned int i = 0; i < _size; ++i)
            _array[i] = other._array[i];
    }

    // Destructor
    ~Array() {
        delete[] _array;
    }

    // Assignment operator
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] _array;
            _size = other._size;
            _array = new T[_size];
            for (unsigned int i = 0; i < _size; ++i)
                _array[i] = other._array[i];
        }
        return *this;
    }

    // Subscript operator
    T& operator[](unsigned int index) {
        if (index >= _size)
            throw std::out_of_range("Index out of bounds");
        return _array[index];
    }

    // Const subscript operator
    const T& operator[](unsigned int index) const {
        if (index >= _size)
            throw std::out_of_range("Index out of bounds");
        return _array[index];
    }

    // Size function
    unsigned int size() const {
        return _size;
    }
};

#endif