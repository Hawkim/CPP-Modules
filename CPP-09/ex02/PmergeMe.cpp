#include "PmergeMe.hpp"
#include <set>
#include <map>
#include <cstdlib>


PmergeMe::PmergeMe(int argc, char** argv) : vecComparisons(0), deqComparisons(0)
{
    if (argc < 2)
        throw std::runtime_error("Usage: ./PmergeMe <numbers...>");

    std::set<int> seen;
    for (int i = 1; i < argc; ++i)
    {
        std::string s(argv[i]);
        if (!isPositiveInteger(s))
            throw std::runtime_error("Error: Invalid number");

        long num = atol(s.c_str());
        if (num <= 0 || num > INT_MAX)
            throw std::runtime_error("Error: Number out of range");

        int n = static_cast<int>(num);
        if (!seen.insert(n).second)
            throw std::runtime_error("Error: Duplicate number");

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
    fordJohnsonSort(vecCopy);
    clock_t endVec = clock();
    double timeVec = (double)(endVec - startVec) * 1e6 / CLOCKS_PER_SEC;

    clock_t startDeq = clock();
    fordJohnsonSort(deqCopy);
    clock_t endDeq = clock();
    double timeDeq = (double)(endDeq - startDeq) * 1e6 / CLOCKS_PER_SEC;

    std::cout << "After: ";
    printContainer(vecCopy);
    printSortCheck(vecCopy);

    std::cout << "Time to process " << vec.size() << " elements with std::vector: "  << timeVec << " us\n";
    std::cout << "Time to process " << deq.size() << " elements with std::deque: "  << timeDeq << " us\n";
    std::cout << "Vector comparisons: " << vecComparisons << "\n";
    std::cout << "Deque comparisons: " << deqComparisons << "\n";
}

bool PmergeMe::isPositiveInteger(const std::string& s) const
{
    if (s.empty()) return false;
    for (std::string::size_type i = 0; i < s.size(); ++i)
        if (!isdigit(s[i])) return false;
    return true;
}

void PmergeMe::printContainer(const std::vector<int>& vec) const
{
    for (std::vector<int>::size_type i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i + 1 < vec.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

void PmergeMe::printContainer(const std::deque<int>& deq) const
{
    for (std::deque<int>::size_type i = 0; i < deq.size(); ++i)
    {
        std::cout << deq[i];
        if (i + 1 < deq.size()) std::cout << " ";
    }
    std::cout << std::endl;
}

int PmergeMe::jacobsthal(int n) const
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, i = 2, tmp;
    while (i <= n)
    {
        tmp = b + 2 * a;
        a = b;
        b = tmp;
        ++i;
    }
    return b;
}

std::vector<int> PmergeMe::generateJacobsthalSequence(int pendSize) const
{
    std::vector<int> seq;
    int i = 2;
    while (true)
    {
        int j = jacobsthal(i);
        if (j > pendSize)
            break;
        seq.push_back(j);
        ++i;
    }
    return seq;
}


std::vector<size_t> PmergeMe::generateInsertionOrder(int pendSize) const
{
    std::vector<int> jacobSeq = generateJacobsthalSequence(pendSize);

    std::vector<size_t> order;
    
    int prev = 0;
    for (std::vector<int>::size_type i = 0; i < jacobSeq.size(); ++i)
    {
        for (int j = jacobSeq[i] - 1; j >= prev; --j)
            if ((size_t)j < (size_t)pendSize)
                order.push_back((size_t)j);
        prev = jacobSeq[i];
    }
    for (int j = pendSize - 1; j >= prev; --j)
        order.push_back((size_t)j);
    return order;
}

size_t PmergeMe::binarySearch(const std::vector<int>& vec, int value, size_t left, size_t right)
{
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        ++vecComparisons;
        if (vec[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    if (vec[left] < value)
        return left + 1;
    return left;
}

size_t PmergeMe::binarySearch(const std::deque<int>& deq, int value, size_t left, size_t right)
{
	//  less comparisons for deque as well
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        ++deqComparisons;
        if (deq[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    if (deq[left] < value)
        return left + 1;
    return left;

}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec)
{
    if (vec.size() <= 1) return;

    bool hasOdd = (vec.size() % 2 != 0);
    int odd = -1;
    if (hasOdd)
    {
        odd = vec.back();
        vec.pop_back();
    }

    std::vector<std::pair<int, int> > pairs;

    for (size_t i = 0; i + 1 < vec.size(); i += 2)
    {
        ++vecComparisons;
        if (vec[i] > vec[i + 1])
            pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        else
            pairs.push_back(std::make_pair(vec[i + 1], vec[i]));
    }

    std::vector<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);
    fordJohnsonSort(mainChain);

    std::map<int, int> winners;
    for (size_t i = 0; i < pairs.size(); ++i)
        winners[pairs[i].first] = pairs[i].second;

    std::vector<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
        pend.push_back(winners[mainChain[i]]);

    std::vector<size_t> partner(mainChain.size());
    for (size_t i = 0; i < mainChain.size(); ++i)
        partner[i] = i;

    if (!pend.empty())
    {
        mainChain.insert(mainChain.begin(), pend[0]);
        for (size_t i = 0; i < partner.size(); ++i)
            ++partner[i];
    }

    std::vector<size_t> order = generateInsertionOrder(pend.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        if (idx == 0 || idx >= pend.size()) continue;
        int val = pend[idx];
        size_t insertPos = binarySearch(mainChain, val, 0, partner[idx] - 1);
        mainChain.insert(mainChain.begin() + insertPos, val);
        for (size_t j = 0; j < partner.size(); ++j)
            if (partner[j] >= insertPos)
                ++partner[j];
    }

    if (hasOdd)
    {
        size_t pos = binarySearch(mainChain, odd, 0, mainChain.size() - 1);
        mainChain.insert(mainChain.begin() + pos, odd);
    }

    vec = mainChain;
}

void PmergeMe::fordJohnsonSort(std::deque<int>& deq)
{
    if (deq.size() <= 1) return;

    bool hasOdd = (deq.size() % 2 != 0);
    int odd = -1;
    if (hasOdd)
    {
        odd = deq.back();
        deq.pop_back();
    }

   std::vector<std::pair<int, int> > pairs;

    for (size_t i = 0; i + 1 < deq.size(); i += 2)
    {
        ++deqComparisons;
        if (deq[i] > deq[i + 1])
            pairs.push_back(std::make_pair(deq[i], deq[i + 1]));
        else
            pairs.push_back(std::make_pair(deq[i + 1], deq[i]));
    }

    std::deque<int> mainChain;
    for (size_t i = 0; i < pairs.size(); ++i)
        mainChain.push_back(pairs[i].first);
    fordJohnsonSort(mainChain);

    std::map<int, int> winners;
    for (size_t i = 0; i < pairs.size(); ++i)
        winners[pairs[i].first] = pairs[i].second;

    std::deque<int> pend;
    for (size_t i = 0; i < mainChain.size(); ++i)
        pend.push_back(winners[mainChain[i]]);

    std::vector<size_t> partner(mainChain.size());
    for (size_t i = 0; i < mainChain.size(); ++i)
        partner[i] = i;

    if (!pend.empty())
    {
        mainChain.push_front(pend[0]);
        for (size_t i = 0; i < partner.size(); ++i)
            ++partner[i];
    }

    std::vector<size_t> order = generateInsertionOrder(pend.size());
    for (size_t i = 0; i < order.size(); ++i)
    {
        size_t idx = order[i];
        if (idx == 0 || idx >= pend.size()) continue;
        int val = pend[idx];
        size_t insertPos = binarySearch(mainChain, val, 0, partner[idx] - 1);
        mainChain.insert(mainChain.begin() + insertPos, val);
        for (size_t j = 0; j < partner.size(); ++j)
            if (partner[j] >= insertPos)
                ++partner[j];
    }

    if (hasOdd)
    {
        size_t pos = binarySearch(mainChain, odd, 0, mainChain.size() - 1);
        mainChain.insert(mainChain.begin() + pos, odd);
    }

    deq = mainChain;
}
