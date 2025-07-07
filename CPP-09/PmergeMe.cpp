#include "PmergeMe.hpp"
#include <set>
#include <algorithm>

void displayDuration(struct timeval& start, struct timeval& end) {
    size_t micros1 = start.tv_sec * 1000000 + start.tv_usec;
    size_t micros2 = end.tv_sec * 1000000 + end.tv_usec;
    size_t delta = micros2 - micros1;
    std::cout << delta << " us";
}

// Binary insert with comparison tracking
template<typename T>
void binaryInsert(T& container, typename T::value_type value, int& comparisons) {
    typename T::iterator it = container.begin();
    typename T::iterator end = container.end();
    while (it != end) {
        comparisons++;
        if (*it > value)
            break;
        ++it;
    }
    container.insert(it, value);
}

// Merge-insert with Jacobsthal insert order (approximate FJ)
std::vector<size_t> generateJacobsthalIndices(size_t n) {
    std::vector<size_t> indices;
    size_t j = 1;
    while (j < n) {
        indices.push_back(j);
        j = 2 * j + 1;
    }
    return indices;
}

template<typename T>
void trueFordJohnsonSort(T& input, int& comparisons) {
    if (input.size() <= 1) return;

    typedef typename T::value_type V;
    std::vector<std::pair<V, V> > pairs;
    V straggler;
    bool hasStraggler = false;

    size_t i = 0;
    for (; i + 1 < input.size(); i += 2) {
        V a = input[i], b = input[i + 1];
        comparisons++;
        if (a > b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    if (i < input.size()) {
        straggler = input[i];
        hasStraggler = true;
    }

    T mainChain;
    for (size_t k = 0; k < pairs.size(); ++k)
        mainChain.push_back(pairs[k].second);

    trueFordJohnsonSort(mainChain, comparisons);

    std::vector<size_t> schedule = generateJacobsthalIndices(pairs.size());
    std::set<size_t> used;

    for (size_t j = 0; j < schedule.size(); ++j) {
        size_t idx = schedule[j];
        if (idx < pairs.size()) {
            binaryInsert(mainChain, pairs[idx].first, comparisons);
            used.insert(idx);
        }
    }

    for (size_t k = 0; k < pairs.size(); ++k) {
        if (used.find(k) == used.end()) {
            binaryInsert(mainChain, pairs[k].first, comparisons);
        }
    }

    if (hasStraggler)
        binaryInsert(mainChain, straggler, comparisons);

    input.assign(mainChain.begin(), mainChain.end());
}

template<typename T>
void mergeInsertSort(T& container, int& comparisons) {
    if (container.size() <= 1) return;

    T left, right;
    for (size_t i = 0; i < container.size(); ++i) {
        if (i % 2 == 0)
            left.push_back(container[i]);
        else
            right.push_back(container[i]);
    }

    mergeInsertSort(left, comparisons);
    for (size_t i = 0; i < right.size(); ++i)
        binaryInsert(left, right[i], comparisons);

    container = left;
}

template<typename T>
void dynamicSort(T& container, int& comparisons) {
    if (container.size() <= 32)
        trueFordJohnsonSort(container, comparisons);
    else
        mergeInsertSort(container, comparisons);
}

void fordJohnsonSort(std::vector<int>& vec, int& comparisons) {
    dynamicSort(vec, comparisons);
}

void fordJohnsonSort(std::deque<int>& deq, int& comparisons) {
    dynamicSort(deq, comparisons);
}

bool parseInput(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq) {
    std::set<int> seen;
    for (int i = 1; i < argc; ++i) {
        std::string s = argv[i];
        for (size_t j = 0; j < s.size(); ++j) {
            if (!isdigit(s[j])) {
                std::cerr << "Error\n";
                return false;
            }
        }
        int num = std::atoi(argv[i]);
        if (num < 0 || seen.count(num)) {
            std::cerr << "Error\n";
            return false;
        }
        seen.insert(num);
        vec.push_back(num);
        deq.push_back(num);
    }
    return true;
}
