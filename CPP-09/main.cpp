#include "PmergeMe.hpp"

int main(int argc, char** argv) {
    std::vector<int> vec;
    std::deque<int> deq;

    if (!parseInput(argc, argv, vec, deq))
        return 1;

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    int compVec = 0, compDeq = 0;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    fordJohnsonSort(vec, compVec);
    gettimeofday(&end, NULL);
    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : ";
    displayDuration(start, end);
    std::cout << " (" << compVec << " comparisons)" << std::endl;

    gettimeofday(&start, NULL);
    fordJohnsonSort(deq, compDeq);
    gettimeofday(&end, NULL);
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : ";
    displayDuration(start, end);
    std::cout << " (" << compDeq << " comparisons)" << std::endl;

    return 0;
}
