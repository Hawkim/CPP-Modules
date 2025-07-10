// PmergeMe.hpp
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <climits>
#include <utility>
#include <set>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <map>

class PmergeMe
{
    public:
        PmergeMe(int argc, char** argv);
        ~PmergeMe();
        void process();

    private:
        std::vector<int> _vec;
        std::deque<int> _deq;
        unsigned long vecComparisons;

        bool isPositiveInteger(const std::string& s) const;
        void printContainer(const std::vector<int>& vec) const;
        void printContainer(const std::deque<int>& deq) const;

        // Ford-Johnson implementation
        void fordJohnsonSort(std::vector<int>& vec);
        void fordJohnsonSort(std::deque<int>& deq);
        int jacobsthal(int n) const;
        std::vector<int> generateJacobsthalSequence(int pendSize) const;
        std::vector<size_t> generateInsertionOrder(int pendSize) const;
        size_t binarySearch(const std::vector<int>& vec, int value, size_t left, size_t right);
        size_t binarySearch(const std::deque<int>& deq, int value, size_t left, size_t right);
};

#endif