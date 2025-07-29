#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <stdexcept>
#include <ctime>

class PmergeMe {
public:
    PmergeMe(int argc, char** argv);
    ~PmergeMe();

    void process();

private:
    std::vector<int> vec;
    std::deque<int> deq;

    size_t vecComparisons;
    size_t deqComparisons;

    bool isPositiveInteger(const std::string& s) const;

    void printContainer(const std::vector<int>& vec) const;
    void printContainer(const std::deque<int>& deq) const;

    void printSortCheck(const std::vector<int>& vec) const {
        for (size_t i = 1; i < vec.size(); ++i) {
            if (vec[i] < vec[i - 1]) {
                std::cout << "✘ Not sorted" << std::endl;
                return;
            }
        }
        std::cout << "✔ Sorted" << std::endl;
    }

    void printSortCheck(const std::deque<int>& deq) const {
        for (size_t i = 1; i < deq.size(); ++i) {
            if (deq[i] < deq[i - 1]) {
                std::cout << "✘ Not sorted" << std::endl;
                return;
            }
        }
        std::cout << "✔ Sorted" << std::endl;
    }

    int jacobsthal(int n) const;
    std::vector<int> generateJacobsthalSequence(int pendSize) const;
    std::vector<size_t> generateInsertionOrder(int pendSize) const;

    // New: templated binary search with partner restriction
    template<typename Container>
    size_t binarySearch(const Container& c, int value, size_t left, size_t right, size_t& count, bool isVec);

    // Updated Ford-Johnson sort signatures (with comparison counter reference)
    void fordJohnsonSort(std::vector<int>& vec, size_t& cmpCount);
    void fordJohnsonSort(std::deque<int>& deq, size_t& cmpCount);
};

#endif
