#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <ctime>
#include <cerrno>
#include <cstdlib>

#define GREEN_CHECK "\033[1;32m✔\033[0m"
#define RED_X       "\033[1;31m✘\033[0m"

static int validate_input(int ac, char** av, std::vector<int>& input) {
    std::set<long> seen;
    for (int i = 1; i < ac; ++i) {
        errno = 0;
        char* endPtr = 0;
        long n = std::strtol(av[i], &endPtr, 10);
        if (*endPtr || n <= 0 || errno == ERANGE) {
            std::cerr << "Error: invalid input '" << av[i] << "'\n";
            return 0;
        }
        if (!seen.insert(n).second) {
            std::cerr << "Error: duplicate number '" << n << "'\n";
            return 0;
        }
        input.push_back((int)n);
    }
    return 1;
}

// static bool isSortedVec(const std::vector<int>& v) {
//     for (std::size_t i = 1; i < v.size(); ++i) if (v[i-1] > v[i]) return false;
//     return true;
// }
// static bool isSortedDeq(const std::deque<int>& d) {
//     for (std::size_t i = 1; i < d.size(); ++i) if (d[i-1] > d[i]) return false;
//     return true;
// }

int main(int ac, char** av) {
    if (ac < 2) { std::cerr << "Usage: ./pmerge <numbers...>\n"; return 1; }

    std::vector<int> input;
    if (!validate_input(ac, av, input)) return 1;

    std::deque<int> input_deque(input.begin(), input.end());

    PmergeMe fj;

    std::cout << "Before: ";
    fj.print_vector(input);

    std::size_t vec_comparisons = 0, deq_comparisons = 0;

    std::clock_t start_v = std::clock();
    fj.FordJohnsonSortVec(input, (int*)&vec_comparisons);
    std::clock_t end_v = std::clock();

    std::cout << "After:  ";
    fj.print_vector(input);

    std::clock_t start_d = std::clock();
    fj.FordJohnsonSortDeq(input_deque, (int*)&deq_comparisons);
    std::clock_t end_d = std::clock();

    double t_vec_us = (double)(end_v - start_v) / CLOCKS_PER_SEC * 1e6;
    double t_deq_us = (double)(end_d - start_d) / CLOCKS_PER_SEC * 1e6;

    // std::cout << "Vector comparisons: " << vec_comparisons << "\n";
    // std::cout << "Deque  comparisons: " << deq_comparisons << "\n";
    std::cout << "Time to process " << input.size() << " elements with std::vector: " << t_vec_us << " us\n";
    std::cout << "Time to process " << input_deque.size() << " elements with std::deque: " << t_deq_us << " us\n";

    // std::cout << "Vector sorted? " << (isSortedVec(input) ? GREEN_CHECK : RED_X) << "\n";
    // std::cout << "Deque  sorted? " << (isSortedDeq(input_deque) ? GREEN_CHECK : RED_X) << "\n";
    return 0;
}
