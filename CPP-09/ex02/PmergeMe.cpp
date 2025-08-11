#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <cstdio>
#include <cstdlib>

// Binary searches with comparison counting
int binary_Search_vector(const std::vector<int>& mainChain, int key, int hi, int* comparisons) {
    if (mainChain.empty()) return 0;
    int lo = 0;
    if (hi >= (int)mainChain.size()) hi = (int)mainChain.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        ++(*comparisons);
        if (mainChain[mid] == key) return mid;
        else if (mainChain[mid] > key) hi = mid - 1;
        else lo = mid + 1;
    }
    return lo;
}

int binary_Search_vector_deque(const std::deque<int>& mainChain, int key, int hi, int* comparisons) {
    if (mainChain.empty()) return 0;
    int lo = 0;
    if (hi >= (int)mainChain.size()) hi = (int)mainChain.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        ++(*comparisons);
        if (mainChain[mid] == key) return mid;
        else if (mainChain[mid] > key) hi = mid - 1;
        else lo = mid + 1;
    }
    return lo;
}

// Jacobsthal + indices
int jacobsthalSeqGen(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int prev2 = 0, prev1 = 1, current = 0;
    for (int i = 2; i <= n; ++i) { current = prev1 + 2 * prev2; prev2 = prev1; prev1 = current; }
    return current;
}

std::vector<int> JacobthalIndices(int pendingCount) {
    std::vector<int> jacobIndices;
    int seqIndex = 3;
    while (jacobsthalSeqGen(seqIndex) <= pendingCount) {
        jacobIndices.push_back(jacobsthalSeqGen(seqIndex));
        ++seqIndex;
    }
    return jacobIndices;
}

std::deque<int> JacobthalIndicesDeq(int pendingCount) {
    std::deque<int> jacobIndices;
    int seqIndex = 3;
    while (jacobsthalSeqGen(seqIndex) <= pendingCount) {
        jacobIndices.push_back(jacobsthalSeqGen(seqIndex));
        ++seqIndex;
    }
    return jacobIndices;
}

// Adapt Jacobsthal to insertion order
void edit(std::vector<int>& jacobIndices, std::vector<int> pending) {
    std::vector<int> seenNumbers;
    std::vector<int> finalOrder;
    for (std::vector<int>::iterator it = jacobIndices.begin(); it != jacobIndices.end(); ++it) {
        if (*it < 0) continue;
        int x = *it;
        while (x > 1) {
            if (std::find(seenNumbers.begin(), seenNumbers.end(), x) == seenNumbers.end()) {
                finalOrder.push_back(x - 1);
                seenNumbers.push_back(x);
            } else break;
            --x;
        }
    }
    if (finalOrder.size() == pending.size()) {
        jacobIndices = finalOrder;
    } else {
        int backfill = (int)pending.size();
        while (finalOrder.size() < pending.size()) {
            if (std::find(seenNumbers.begin(), seenNumbers.end(), backfill) == seenNumbers.end()) {
                finalOrder.push_back(backfill - 1);
                seenNumbers.push_back(backfill);
            } else break;
            --backfill;
        }
        jacobIndices = finalOrder;
    }
}

void editDeq(std::deque<int>& jacobIndices, std::deque<int> pending) {
    std::deque<int> seenNumbers;
    std::deque<int> finalOrder;
    for (std::deque<int>::iterator it = jacobIndices.begin(); it != jacobIndices.end(); ++it) {
        if (*it < 0) continue;
        int x = *it;
        while (x > 1) {
            if (std::find(seenNumbers.begin(), seenNumbers.end(), x) == seenNumbers.end()) {
                finalOrder.push_back(x - 1);
                seenNumbers.push_back(x);
            } else break;
            --x;
        }
    }
    if (finalOrder.size() == pending.size()) {
        jacobIndices = finalOrder;
    } else {
        int backfill = (int)pending.size();
        while (finalOrder.size() < pending.size()) {
            if (std::find(seenNumbers.begin(), seenNumbers.end(), backfill) == seenNumbers.end()) {
                finalOrder.push_back(backfill - 1);
                seenNumbers.push_back(backfill);
            } else break;
            --backfill;
        }
        jacobIndices = finalOrder;
    }
}

// Lookups functionss and indices
int get_idx(std::vector<int>& array, int value) {
    if (value == -1) return (int)array.size();
    std::vector<int>::iterator it = std::find(array.begin(), array.end(), value);
    return (it != array.end()) ? (int)std::distance(array.begin(), it) : -1;
}

int get_idx_deq(std::deque<int>& array, int value) {
    if (value == -1) return (int)array.size();
    std::deque<int>::iterator it = std::find(array.begin(), array.end(), value);
    return (it != array.end()) ? (int)std::distance(array.begin(), it) : -1;
}

int findPairedValue(const std::vector<std::pair<int,int> >& pairs, int loserValue) {
    for (std::vector<std::pair<int,int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
        if (it->second == loserValue) return it->first;
    return -1;
}

int findPairedValueDeq(const std::deque<std::pair<int,int> >& pairs, int loserValue) {
    for (std::deque<std::pair<int,int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
        if (it->second == loserValue) return it->first;
    return -1;
}

int findPairedValueFirst(const std::vector<std::pair<int,int> >& pairs, int winnerValue) {
    for (std::vector<std::pair<int,int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
        if (it->first == winnerValue) return it->second;
    return -1;
}

int findPairedValueFirstDeq(const std::deque<std::pair<int,int> >& pairs, int winnerValue) {
    for (std::deque<std::pair<int,int> >::const_iterator it = pairs.begin(); it != pairs.end(); ++it)
        if (it->first == winnerValue) return it->second;
    return -1;
}

std::vector<int> arrangeLosers(std::vector<std::pair<int,int> > mainPairs,
                               std::vector<int> losersInput,
                               std::vector<int> winnersSorted,
                               int oddValue)
{
    std::vector<int> losersReordered;
    for (std::vector<int>::iterator it = winnersSorted.begin(); it != winnersSorted.end(); ++it) {
        int winner = *it;
        int pairedLoser = findPairedValueFirst(mainPairs, winner);
        losersReordered.push_back(pairedLoser);
    }
    if (oddValue != -1) losersReordered.push_back(oddValue);
    losersInput.swap(losersReordered);
    return losersInput;
}

std::deque<int> arrangeLosersDeq(std::deque<std::pair<int,int> > mainPairs,
                                 std::deque<int> losersInput,
                                 std::deque<int> winnersSorted,
                                 int oddValue)
{
    std::deque<int> losersReordered;
    for (std::deque<int>::iterator it = winnersSorted.begin(); it != winnersSorted.end(); ++it) {
        int winner = *it;
        int pairedLoser = findPairedValueFirstDeq(mainPairs, winner);
        losersReordered.push_back(pairedLoser);
    }
    if (oddValue != -1) losersReordered.push_back(oddValue);
    losersInput.swap(losersReordered);
    return losersInput;
}
 

// ===== PmergeMe methods =====

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) { if (this != &other) { (void)other; } return *this; }
PmergeMe::~PmergeMe() {}

void PmergeMe::print_paired_vec(std::vector<std::pair<int, int> > pairs) {
    for (std::size_t i = 0; i < pairs.size(); ++i)
        std::cout << "(" << pairs[i].first << ", " << pairs[i].second << ") ";
    std::cout << std::endl;
}

void PmergeMe::print_vector(const std::vector<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 < values.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::print_deque(const std::deque<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        std::cout << values[i];
        if (i + 1 < values.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::FordJohnsonSortVec(std::vector<int>& values, int* comparisons) {
    if (values.size() <= 1) return;

    std::vector<std::pair<int,int> > pairs; // (winner, loser)
    std::vector<int> winners, losers;
    int oddValue = -1;

    for (std::size_t i = 0; i < values.size(); i += 2) {
        if (i + 1 < values.size()) {
            ++(*comparisons);
            if (values[i] > values[i + 1]) std::swap(values[i], values[i + 1]);
            pairs.push_back(std::make_pair(values[i + 1], values[i]));
        } else {
            oddValue = values[i];
        }
    }

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        winners.push_back(pairs[i].first);
        losers.push_back(pairs[i].second);
    }
    if (oddValue != -1) losers.push_back(oddValue);

    FordJohnsonSortVec(winners, comparisons);                // recursively sort main chain
    losers = arrangeLosers(pairs, losers, winners, oddValue); // align losers

    std::vector<int> insertionOrder = JacobthalIndices((int)losers.size());
    edit(insertionOrder, losers);

    if (insertionOrder.size() > 1) { // pre-insert first loser
        winners.insert(winners.begin(), losers[0]);
        losers[0] = -1;
    }

    for (std::vector<int>::iterator it = insertionOrder.begin(); it != insertionOrder.end(); ++it) {
        int loserIdx = *it;
        if (loserIdx < 0 || (std::size_t)loserIdx >= losers.size()) continue;
        int loserValue = losers[loserIdx];
        if (loserValue == -1) continue;

        int partnerWinner = findPairedValue(pairs, loserValue);
        int upperBound = get_idx(winners, partnerWinner) - 1;

        std::vector<int>::iterator insertPos =
            winners.begin() + binary_Search_vector(winners, loserValue, upperBound, comparisons);
        winners.insert(insertPos, loserValue);
    }

    values.swap(winners);
}

void PmergeMe::FordJohnsonSortDeq(std::deque<int>& values, int* comparisons) {
    if (values.size() <= 1) return;

    std::deque<std::pair<int,int> > pairs; // (winner, loser)
    std::deque<int> winners, losers;
    int oddValue = -1;

    for (std::size_t i = 0; i < values.size(); i += 2) {
        if (i + 1 < values.size()) {
            ++(*comparisons);
            if (values[i] > values[i + 1]) std::swap(values[i], values[i + 1]);
            pairs.push_back(std::make_pair(values[i + 1], values[i]));
        } else {
            oddValue = values[i];
        }
    }

    for (std::size_t i = 0; i < pairs.size(); ++i) {
        winners.push_back(pairs[i].first);
        losers.push_back(pairs[i].second);
    }
    if (oddValue != -1) losers.push_back(oddValue);

    FordJohnsonSortDeq(winners, comparisons);
    losers = arrangeLosersDeq(pairs, losers, winners, oddValue);

    std::deque<int> insertionOrder = JacobthalIndicesDeq((int)losers.size());
    editDeq(insertionOrder, losers);

    if (insertionOrder.size() > 1) {
        winners.insert(winners.begin(), losers[0]);
        losers[0] = -1;
    }

    for (std::deque<int>::iterator it = insertionOrder.begin(); it != insertionOrder.end(); ++it) {
        int loserIdx = *it;
        if (loserIdx < 0 || (std::size_t)loserIdx >= losers.size()) continue;
        int loserValue = losers[loserIdx];
        if (loserValue == -1) continue;

        int partnerWinner = findPairedValueDeq(pairs, loserValue);
        int upperBound = get_idx_deq(winners, partnerWinner) - 1;

        std::deque<int>::iterator insertPos =
            winners.begin() + binary_Search_vector_deque(winners, loserValue, upperBound, comparisons);
        winners.insert(insertPos, loserValue);
    }

    values.swap(winners);
}
