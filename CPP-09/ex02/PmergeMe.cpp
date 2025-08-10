#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <cstdlib>

// ===== Utilities used by the algorithm =====

static int binary_Search(const std::vector<int>& main_chain, int elem, int high, int* comparisons) {
    if (main_chain.empty())
        return 0;
    int low = 0;
    if (high >= static_cast<int>(main_chain.size()))
        high = static_cast<int>(main_chain.size()) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        (*comparisons)++;
        if (main_chain[mid] == elem) {
            return mid;
        } else if (main_chain[mid] > elem) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}

static int binary_Search_deque(const std::deque<int>& main_chain, int elem, int high, int* comparisons) {
    if (main_chain.empty())
        return 0;
    int low = 0;
    if (high >= static_cast<int>(main_chain.size()))
        high = static_cast<int>(main_chain.size()) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        (*comparisons)++;
        if (main_chain[mid] == elem)
            return mid;
        else if (main_chain[mid] > elem)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return low;
}

static int jacobsthalSeqGen(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int prev2 = 0, prev1 = 1, curr = 0;
    for (int i = 2; i <= n; i++) {
        curr = prev1 + 2 * prev2;
        prev2 = prev1;
        prev1 = curr;
    }
    return curr;
}

static std::vector<int> JacobthalIndices(int size) {
    std::vector<int> jacobSequence;
    int jacobIndex = 3;
    while (jacobsthalSeqGen(jacobIndex) <= size) {
        jacobSequence.push_back(jacobsthalSeqGen(jacobIndex));
        jacobIndex++;
    }
    return jacobSequence;
}

static std::deque<int> JacobthalIndicesDeq(int size) {
    std::deque<int> jacobSequence;
    int jacobIndex = 3;
    while (jacobsthalSeqGen(jacobIndex) <= size) {
        jacobSequence.push_back(jacobsthalSeqGen(jacobIndex));
        jacobIndex++;
    }
    return jacobSequence;
}

static void edit(std::vector<int>& jacob, std::vector<int> pend) {
    std::vector<int>::iterator it = jacob.begin();
    std::vector<int> pushedNumbers;
    std::vector<int> temp;
    while (it != jacob.end()) {
        int x;
        if (*it >= 0) {
            x = *it;
            while (x > 1) {
                if (std::find(pushedNumbers.begin(), pushedNumbers.end(), x) == pushedNumbers.end()) {
                    temp.push_back(x - 1);
                    pushedNumbers.push_back(x);
                } else
                    break;
                x--;
            }
        }
        ++it;
    }
    if (temp.size() == pend.size())
        jacob = temp;
    else {
        int x = static_cast<int>(pend.size());
        while (temp.size() < pend.size()) {
            if (std::find(pushedNumbers.begin(), pushedNumbers.end(), x) == pushedNumbers.end()) {
                temp.push_back(x - 1);
                pushedNumbers.push_back(x);
            } else
                break;
            x--;
        }
        jacob = temp;
    }
}

static void editDeq(std::deque<int>& jacob, std::deque<int> pend) {
    std::deque<int>::iterator it = jacob.begin();
    std::deque<int> pushedNumbers;
    std::deque<int> temp;
    while (it != jacob.end()) {
        int x;
        if (*it >= 0) {
            x = *it;
            while (x > 1) {
                if (std::find(pushedNumbers.begin(), pushedNumbers.end(), x) == pushedNumbers.end()) {
                    temp.push_back(x - 1);
                    pushedNumbers.push_back(x);
                } else
                    break;
                x--;
            }
        }
        ++it;
    }
    if (temp.size() == pend.size())
        jacob = temp;
    else {
        int x = static_cast<int>(pend.size());
        while (temp.size() < pend.size()) {
            if (std::find(pushedNumbers.begin(), pushedNumbers.end(), x) == pushedNumbers.end()) {
                temp.push_back(x - 1);
                pushedNumbers.push_back(x);
            } else
                break;
            x--;
        }
        jacob = temp;
    }
}

static int get_idx(std::vector<int>& vec, int val) {
    if (val == -1)
        return static_cast<int>(vec.size());
    std::vector<int>::iterator it = std::find(vec.begin(), vec.end(), val);
    if (it != vec.end())
        return static_cast<int>(std::distance(vec.begin(), it));
    return -1;
}

static int get_idx_deq(std::deque<int>& vec, int val) {
    if (val == -1)
        return static_cast<int>(vec.size());
    std::deque<int>::iterator it = std::find(vec.begin(), vec.end(), val);
    if (it != vec.end())
        return static_cast<int>(std::distance(vec.begin(), it));
    return -1;
}

static int findPairedValue(const std::vector<std::pair<int, int> >& vec, int target) {
    for (std::vector<std::pair<int, int> >::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        if (it->second == target)
            return it->first;
    }
    return -1;
}

static int findPairedValueDeq(const std::deque<std::pair<int, int> >& vec, int target) {
    for (std::deque<std::pair<int, int> >::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        if (it->second == target)
            return it->first;
    }
    return -1;
}

static int findPairedValueFirst(const std::vector<std::pair<int, int> >& vec, int target) {
    for (std::vector<std::pair<int, int> >::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        if (it->first == target)
            return it->second;
    }
    return -1;
}

static int findPairedValueFirstDeq(const std::deque<std::pair<int, int> >& vec, int target) {
    for (std::deque<std::pair<int, int> >::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        if (it->first == target)
            return it->second;
    }
    return -1;
}

static std::vector<int> arrangeLosers(std::vector<std::pair<int, int> > main_chain,
                                      std::vector<int> losers,
                                      std::vector<int> winners,
                                      int odd) {
    std::vector<int> temp;
    for (std::vector<int>::iterator it = winners.begin(); it != winners.end(); ++it) {
        int val = *it;
        int x = findPairedValueFirst(main_chain, val);
        temp.push_back(x);
    }
    if (odd != -1)
        temp.push_back(odd);
    losers.swap(temp);
    return losers;
}

static std::deque<int> arrangeLosersDeq(std::deque<std::pair<int, int> > main_chain,
                                        std::deque<int> losers,
                                        std::deque<int> winners,
                                        int odd) {
    std::deque<int> temp;
    for (std::deque<int>::iterator it = winners.begin(); it != winners.end(); ++it) {
        int val = *it;
        int x = findPairedValueFirstDeq(main_chain, val);
        temp.push_back(x);
    }
    if (odd != -1)
        temp.push_back(odd);
    losers.swap(temp);
    return losers;
}

// ===== PmergeMe methods =====

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) { if (this != &other) { (void)other; } return *this; }
PmergeMe::~PmergeMe() {}

void PmergeMe::print_paired_vec(std::vector<std::pair<int, int> > vec) {
    for (std::size_t i = 0; i < vec.size(); i++)
        std::cout << "(" << vec[i].first << ", " << vec[i].second << ") ";
    std::cout << std::endl;
}

void PmergeMe::print_vector(const std::vector<int>& vec) {
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::print_deque(const std::deque<int>& dq) {
    for (std::size_t i = 0; i < dq.size(); ++i)
        std::cout << dq[i] << (i + 1 < dq.size() ? " " : "");
    std::cout << std::endl;
}

void PmergeMe::sort_vec(std::vector<int>& vec, int* comparisons) {
    if (vec.size() <= 1) return;

    std::vector<std::pair<int, int> > main_chain;
    std::vector<int> winners, losers;
    int odd = -1;

    for (std::size_t i = 0; i < vec.size(); i += 2) {
        if (i + 1 < vec.size()) {
            (*comparisons)++;
            if (vec[i] > vec[i + 1])
                std::swap(vec[i], vec[i + 1]);
            main_chain.push_back(std::make_pair(vec[i + 1], vec[i]));
        } else {
            odd = vec[i];
        }
    }

    for (std::size_t i = 0; i < main_chain.size(); ++i) {
        winners.push_back(main_chain[i].first);
        losers.push_back(main_chain[i].second);
    }
    if (odd != -1)
        losers.push_back(odd);

    sort_vec(winners, comparisons);

    // Rearrange losers to match winners’ paired ordering
    losers = arrangeLosers(main_chain, losers, winners, odd);

    // Generate and adapt Jacobsthal-based insertion order
    std::vector<int> insertion_order = JacobthalIndices(static_cast<int>(losers.size()));
    edit(insertion_order, losers);

    // Pre-insert first loser if sequence has more than one element
    if (insertion_order.size() > 1) {
        winners.insert(winners.begin(), losers[0]);
        losers[0] = -1;
    }

    // Insert remaining losers using binary search with upper bound limit
    for (std::vector<int>::iterator it = insertion_order.begin(); it != insertion_order.end(); ++it) {
        int index = *it;
        if (index < 0 || static_cast<std::size_t>(index) >= losers.size())
            continue;
        int val = losers[index];
        if (val == -1)
            continue;
        int lim = get_idx(winners, findPairedValue(main_chain, val)) - 1;
        std::vector<int>::iterator pos = winners.begin() + binary_Search(winners, val, lim, comparisons);
        winners.insert(pos, val);
    }

    vec.swap(winners);
}

void PmergeMe::sort_deque(std::deque<int>& dq, int* comparisons) {
    if (dq.size() <= 1) return;

    std::deque<std::pair<int, int> > main_chain;
    std::deque<int> winners, losers;
    int odd = -1;

    for (std::size_t i = 0; i < dq.size(); i += 2) {
        if (i + 1 < dq.size()) {
            (*comparisons)++;
            if (dq[i] > dq[i + 1])
                std::swap(dq[i], dq[i + 1]);
            main_chain.push_back(std::make_pair(dq[i + 1], dq[i]));
        } else {
            odd = dq[i];
        }
    }

    for (std::size_t i = 0; i < main_chain.size(); ++i) {
        winners.push_back(main_chain[i].first);
        losers.push_back(main_chain[i].second);
    }
    if (odd != -1)
        losers.push_back(odd);

    sort_deque(winners, comparisons);

    // Rearrange losers to match winners’ paired ordering
    losers = arrangeLosersDeq(main_chain, losers, winners, odd);

    // Generate and adapt Jacobsthal-based insertion order
    std::deque<int> insertion_order = JacobthalIndicesDeq(static_cast<int>(losers.size()));
    editDeq(insertion_order, losers);

    // Pre-insert first loser if sequence has more than one element
    if (insertion_order.size() > 1) {
        winners.insert(winners.begin(), losers[0]);
        losers[0] = -1;
    }

    // Insert remaining losers using binary search with upper bound limit
    for (std::deque<int>::iterator it = insertion_order.begin(); it != insertion_order.end(); ++it) {
        int index = *it;
        if (index < 0 || static_cast<std::size_t>(index) >= losers.size())
            continue;
        int val = losers[index];
        if (val == -1)
            continue;
        int lim = get_idx_deq(winners, findPairedValueDeq(main_chain, val)) - 1;
        std::deque<int>::iterator pos = winners.begin() + binary_Search_deque(winners, val, lim, comparisons);
        winners.insert(pos, val);
    }

    dq.swap(winners);
}
