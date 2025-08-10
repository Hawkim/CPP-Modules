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
    void sort_vec(std::vector<int>& vec, int* comparisons);
    void sort_deque(std::deque<int>& dq, int* comparisons);

    // Simple printers (handy for the project’s required output)
    void print_vector(const std::vector<int>& vec);
    void print_deque(const std::deque<int>& dq);
    void print_paired_vec(std::vector<std::pair<int, int> > vec);
};

#endif // PMERGEME_HPP
