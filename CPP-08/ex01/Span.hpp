#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>

class Span {
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

public:
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int number);
    template <typename Iterator>
    void addRange(Iterator begin, Iterator end) {
        unsigned int remaining = _maxSize - _numbers.size();
        unsigned int distance = std::distance(begin, end);
        
        if (distance > remaining) {
            throw std::length_error("Not enough space in Span");
        }
        _numbers.insert(_numbers.end(), begin, end);
    }
    
    int shortestSpan() const;
    int longestSpan() const;

    unsigned int size() const;
    unsigned int capacity() const;
};

#endif
