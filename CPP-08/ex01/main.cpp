#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    // Basic test from subject
    std::cout << "=== Basic Test ===" << std::endl;
    {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    }

    // Test with 10,000 numbers
    std::cout << "\n=== Large Test (10,000 numbers) ===" << std::endl;
    {
        Span sp(10000);
        for (int i = 0; i < 10000; ++i) {
            sp.addNumber(i * 2);
        }
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    }

    // Test with random numbers
    std::cout << "\n=== Random Numbers Test ===" << std::endl;
    {
        std::srand(std::time(0));
        Span sp(1000);
        for (int i = 0; i < 1000; ++i) {
            sp.addNumber(std::rand() % 10000);
        }
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    }

    // Test with range of iterators
    std::cout << "\n=== Iterator Range Test ===" << std::endl;
    {
        Span sp(20);
        std::vector<int> vec;
        for (int i = 0; i < 10; ++i) {
            vec.push_back(i * 3);
        }
        
        sp.addRange(vec.begin(), vec.end());
        std::cout << "Added " << sp.size() << " numbers" << std::endl;
        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;
    }

    // Test exceptions
    std::cout << "\n=== Exception Tests ===" << std::endl;
    {
        // Empty span
        try {
            Span sp(5);
            std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << std::endl;
        }

        // Full span
        try {
            Span sp(2);
            sp.addNumber(1);
            sp.addNumber(2);
            sp.addNumber(3);
        } catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << std::endl;
        }

        // Range too large
        try {
            Span sp(5);
            std::vector<int> vec(10, 42);
            sp.addRange(vec.begin(), vec.end());
        } catch (const std::exception& e) {
            std::cout << "Expected error: " << e.what() << std::endl;
        }
    }

    return 0;
}
