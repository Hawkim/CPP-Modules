#include "PmergeMe.hpp"
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <ctime>

// Comparison helpers for counting
inline bool cmpVecGreater(int a, int b, size_t& c) { ++c; return a > b; }
inline bool cmpVecLess(int a, int b, size_t& c) { ++c; return a < b; }
inline bool cmpDeqGreater(int a, int b, size_t& c) { ++c; return a > b; }
inline bool cmpDeqLess(int a, int b, size_t& c) { ++c; return a < b; }

PmergeMe::PmergeMe(int argc, char** argv) : vecComparisons(0), deqComparisons(0)
{
    if (argc < 2) throw std::runtime_error("Usage: ./PmergeMe <numbers...>");
    std::vector<int> seen;
    for (int i = 1; i < argc; ++i)
    {
        std::string s(argv[i]);
        if (!isPositiveInteger(s)) throw std::runtime_error("Error: Invalid number");

        long num = atol(s.c_str());
        if (num <= 0 || num > INT_MAX) throw std::runtime_error("Error: Number out of range");

        int n = num;
        if (std::find(seen.begin(), seen.end(), n) != seen.end())
            throw std::runtime_error("Error: Duplicate number");

        seen.push_back(n);
        vec.push_back(n);
        deq.push_back(n);
    }
}

PmergeMe::~PmergeMe() {}

void PmergeMe::process()
{
    std::cout << "Before: ";
    printContainer(vec);

    std::vector<int> vecCopy(vec);
    std::deque<int> deqCopy(deq);

    clock_t startVec = clock();
    fordJohnsonSort(vecCopy, vecComparisons);
    clock_t endVec = clock();
    double timeVec = (double)(endVec - startVec) * 1e6 / CLOCKS_PER_SEC;

    clock_t startDeq = clock();
    fordJohnsonSort(deqCopy, deqComparisons);
    clock_t endDeq = clock();
    double timeDeq = (double)(endDeq - startDeq) * 1e6 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    printContainer(vecCopy);
    std::cout << "Time to process " << vec.size() << " elements with std::vector: " << timeVec << " us\n";
    std::cout << "Time to process " << deq.size() << " elements with std::deque: " << timeDeq << " us\n";
    std::cout << "Vector comparisons: " << vecComparisons << "\n";
    std::cout << "Deque comparisons: " << deqComparisons << "\n";

    printSortCheck(vecCopy);
    printSortCheck(deqCopy);
}

bool PmergeMe::isPositiveInteger(const std::string& s) const
{
    if (s.empty()) return false;
    for (std::string::size_type i = 0; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

void PmergeMe::printContainer(const std::vector<int>& v) const
{
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printContainer(const std::deque<int>& d) const
{
    for (size_t i = 0; i < d.size(); ++i) {
        std::cout << d[i];
        if (i + 1 < d.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

int PmergeMe::jacobsthal(int n) const
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, i = 2, tmp;
    while (i <= n) {
        tmp = b + 2 * a;
        a = b;
        b = tmp;
        ++i;
    }
    return b;
}

std::vector<int> PmergeMe::generateJacobsthalSequence(int size) const
{
    std::vector<int> seq;
    for (int i = 2;; ++i) {
        int j = jacobsthal(i);
        if (j > size) break;
        seq.push_back(j);
    }
    return seq;
}

std::vector<size_t> PmergeMe::generateInsertionOrder(int pendSize) const
{
    std::vector<int> jacob = generateJacobsthalSequence(pendSize);
    std::vector<size_t> order;
    int prev = 0;
    for (size_t i = 0; i < jacob.size(); ++i) {
        for (int j = jacob[i] - 1; j >= prev; --j)
            if ((size_t)j < (size_t)pendSize) order.push_back(j);
        prev = jacob[i];
    }
    for (int j = pendSize - 1; j >= prev; --j)
        order.push_back(j);
    return order;
}

// Binary search template
template<typename Container>
size_t PmergeMe::binarySearch(const Container& c, int value, size_t left, size_t right, size_t& count, bool isVec)
{
    while (left < right) {
        size_t mid = left + (right - left) / 2;
        bool less = isVec ? cmpVecLess(c[mid], value, count) : cmpDeqLess(c[mid], value, count);
        if (less)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec, size_t& cmpCount)
{
    if (vec.size() <= 1) return;

    bool hasOdd = vec.size() % 2;
    int odd = -1;
    if (hasOdd) { odd = vec.back(); vec.pop_back(); }

    std::vector< std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < vec.size(); i += 2) {
        if (cmpVecGreater(vec[i], vec[i+1], cmpCount))
            pairs.push_back(std::make_pair(vec[i], vec[i+1]));
        else
            pairs.push_back(std::make_pair(vec[i+1], vec[i]));
    }

    std::vector<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i) mainChain.push_back(pairs[i].first);
    fordJohnsonSort(mainChain, cmpCount);

    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
        for (size_t j = 0; j < pairs.size(); ++j)
            if (pairs[j].first == mainChain[i]) { pend.push_back(pairs[j].second); break; }

    std::vector<size_t> partner(mainChain.size());
    for (size_t i = 0; i < mainChain.size(); ++i) partner[i] = i;

    if (!pend.empty()) {
        mainChain.insert(mainChain.begin(), pend[0]);
        for (size_t i = 0; i < partner.size(); ++i) ++partner[i];
    }

    std::vector<size_t> order = generateInsertionOrder(pend.size());
    for (size_t i = 0; i < order.size(); ++i) {
        size_t idx = order[i];
        if (idx == 0 || idx >= pend.size()) continue;
        int val = pend[idx];
        size_t limit = partner[idx]; // STRICT partner bound
        size_t pos = binarySearch(mainChain, val, 0, limit, cmpCount, true);
        mainChain.insert(mainChain.begin() + pos, val);
        for (size_t j = 0; j < partner.size(); ++j)
            if (partner[j] >= pos) ++partner[j];
    }

    if (hasOdd) {
        size_t pos = binarySearch(mainChain, odd, 0, mainChain.size(), cmpCount, true);
        mainChain.insert(mainChain.begin() + pos, odd);
    }

    vec = mainChain;
}

void PmergeMe::fordJohnsonSort(std::deque<int>& deq, size_t& cmpCount)
{
    if (deq.size() <= 1) return;

    bool hasOdd = deq.size() % 2;
    int odd = -1;
    if (hasOdd) { odd = deq.back(); deq.pop_back(); }

    std::vector< std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < deq.size(); i += 2) {
        if (cmpDeqGreater(deq[i], deq[i+1], cmpCount))
            pairs.push_back(std::make_pair(deq[i], deq[i+1]));
        else
            pairs.push_back(std::make_pair(deq[i+1], deq[i]));
    }

    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i) mainChain.push_back(pairs[i].first);
    fordJohnsonSort(mainChain, cmpCount);

    std::deque<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
        for (size_t j = 0; j < pairs.size(); ++j)
            if (pairs[j].first == mainChain[i]) { pend.push_back(pairs[j].second); break; }

    std::vector<size_t> partner(mainChain.size());
    for (size_t i = 0; i < mainChain.size(); ++i) partner[i] = i;

    if (!pend.empty()) {
        mainChain.push_front(pend[0]);
        for (size_t i = 0; i < partner.size(); ++i) ++partner[i];
    }

    std::vector<size_t> order = generateInsertionOrder(pend.size());
    for (size_t i = 0; i < order.size(); ++i) {
        size_t idx = order[i];
        if (idx == 0 || idx >= pend.size()) continue;
        int val = pend[idx];
        size_t limit = partner[idx];
        size_t pos = binarySearch(mainChain, val, 0, limit, cmpCount, false);
        mainChain.insert(mainChain.begin() + pos, val);
        for (size_t j = 0; j < partner.size(); ++j)
            if (partner[j] >= pos) ++partner[j];
    }

    if (hasOdd) {
        size_t pos = binarySearch(mainChain, odd, 0, mainChain.size(), cmpCount, false);
        mainChain.insert(mainChain.begin() + pos, odd);
    }

    deq = mainChain;
}
