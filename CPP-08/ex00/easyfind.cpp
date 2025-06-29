#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <climits>
#include "easyfind.hpp"

int main() {
    // Test 1: Vector with basic values
    std::cout << "\n=== TEST 1: Vector Basic Test ===\n";
    {
        std::vector<int> vec;
        for (int i = 0; i < 10; ++i) vec.push_back(i * 2);
        
        // Find existing value
        try {
            int value = 4;
            std::vector<int>::iterator it = easyfind(vec, value);
            std::cout << "Found " << value << " at position: " << (it - vec.begin()) << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
        
        // Find non-existing value
        try {
            easyfind(vec, 5);
            std::cout << "Found 5\n";
        } catch (const std::exception& e) {
            std::cout << "5 not found (expected)\n";
        }
    }

    // Test 2: List with negative values
    std::cout << "\n=== TEST 2: List with Negative Values ===\n";
    {
        std::list<int> lst;
        lst.push_back(-5);
        lst.push_back(-3);
        lst.push_back(0);
        lst.push_back(3);
        lst.push_back(5);
        
        try {
            easyfind(lst, -3);
            std::cout << "Found -3 in list\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    // Test 3: Deque with duplicates
    std::cout << "\n=== TEST 3: Deque with Duplicates ===\n";
    {
        std::deque<int> dq;
        dq.push_back(1);
        dq.push_back(2);
        dq.push_back(2);
        dq.push_back(3);
        
        try {
            std::deque<int>::iterator it = easyfind(dq, 2);
            std::cout << "Found first 2 at position: " << (it - dq.begin()) << "\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    // Test 4: Empty container
    std::cout << "\n=== TEST 4: Empty Container ===\n";
    {
        std::vector<int> emptyVec;
        try {
            easyfind(emptyVec, 42);
            std::cout << "Found 42 in empty vector (unexpected)\n";
        } catch (const std::exception& e) {
            std::cout << "Correctly failed to find in empty container: " << e.what() << "\n";
        }
    }

    // Test 5: Edge values
    std::cout << "\n=== TEST 5: Edge Values ===\n";
    {
        std::vector<int> edgeVec;
        edgeVec.push_back(INT_MAX);
        edgeVec.push_back(INT_MIN);
        
        try {
            easyfind(edgeVec, INT_MAX);
            std::cout << "Found INT_MAX\n";
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    return 0;
}