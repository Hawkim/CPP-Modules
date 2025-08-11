#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <utility>
#include <cstddef>

class PmergeMe {
public:
    PmergeMe();
    PmergeMe(const PmergeMe& other);
    PmergeMe& operator=(const PmergeMe& other);
    ~PmergeMe();

    // Sorting (counts comparisons via the provided pointer)
    void FordJohnsonSortVec(std::vector<int>& values, int* comparisons);
    void FordJohnsonSortDeq(std::deque<int>& values, int* comparisons);

    // Simple printers (handy for the project’s required output)
    void print_vector(const std::vector<int>& values);
    void print_deque(const std::deque<int>& values);
    void print_paired_vec(std::vector<std::pair<int, int> > pairs);
};

#endif // PMERGEME_HPP
