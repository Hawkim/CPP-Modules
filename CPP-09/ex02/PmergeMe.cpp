#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char** argv) : vecComparisons(0)
{
	if (argc < 2)
		throw std::runtime_error("Usage: ./PmergeMe <numbers...>");

	std::set<int> uniqueNumbers;

	for (int i = 1; i < argc; ++i)
	{
		std::string s(argv[i]);
		if (!isPositiveInteger(s))
			throw std::runtime_error("Error: Invalid number");

		long num = std::atol(s.c_str());
		if (num <= 0 || num > INT_MAX)
			throw std::runtime_error("Error: Number out of range");

		// Check for duplicate
		int intNum = static_cast<int>(num);
		if (!uniqueNumbers.insert(intNum).second)
			throw std::runtime_error("Error: Duplicate number found");

		_vec.push_back(intNum);
		_deq.push_back(intNum);
	}
}

PmergeMe::~PmergeMe() {}

void PmergeMe::process()
{
	std::cout << "Before: ";
	printContainer(_vec);

	std::vector<int> vecCopy = _vec;
	std::deque<int> deqCopy = _deq;

	clock_t startVec = clock();
	fordJohnsonSort(vecCopy);
	clock_t endVec = clock();
	double timeVec = double(endVec - startVec) * 1e6 / CLOCKS_PER_SEC;

	clock_t startDeq = clock();
	fordJohnsonSort(deqCopy);
	clock_t endDeq = clock();
	double timeDeq = double(endDeq - startDeq) * 1e6 / CLOCKS_PER_SEC;

	std::cout << "After: ";
	printContainer(vecCopy);

	// std::cout << "After (vector): ";
	// printContainer(vecCopy);

	// std::cout << "After (deque): ";
	// printContainer(deqCopy);

	std::cout << "Time to process " << _vec.size() << " elements with std::vector: "  << timeVec << " us\n";
	std::cout << "Time to process " << _deq.size() << " elements with std::deque: "  << timeDeq << " us\n";
	std::cout << "Vector comparisons: " << vecComparisons << "\n";
}

int PmergeMe::jacobsthal(int n) const
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	int prev = 0;
	int curr = 1;

	for (int i = 2; i <= n; ++i)
	{
		int next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return curr;
}


std::vector<int> PmergeMe::generateJacobsthalSequence(int pendSize) const
{
	std::vector<int> sequence;
	int n = 2;

	while (true)
	{
		int val = jacobsthal(n);
		if (val > pendSize)
			break;

		sequence.push_back(val);
		n++;
	}
	return sequence;
}

std::vector<size_t> PmergeMe::generateInsertionOrder(int pendSize) const
{
	std::vector<int> jacobSeq = generateJacobsthalSequence(pendSize);
	std::vector<size_t> order;

	size_t prev = 0;
	for (size_t i = 0; i < jacobSeq.size(); ++i)
	{
		for (size_t j = jacobSeq[i]; j > static_cast<size_t>(prev); --j)
			if (j - 1 < static_cast<size_t>(pendSize))
				order.push_back(j - 1);
		prev = jacobSeq[i];
	}

	for (int j = pendSize; j > static_cast<int>(prev); --j)
		order.push_back(j - 1);

	return order;
}


size_t PmergeMe::binarySearch(const std::vector<int>& vec, int value, size_t left, size_t right)
{
	while (left <= right)
	{
		size_t mid = left + (right - left) / 2;
		vecComparisons++;

		if (vec[mid] < value)
			left = mid + 1;
		else
		{
			if (mid == 0)
				break;
			right = mid - 1;
		}
	}
	return left;
}


size_t PmergeMe::binarySearch(const std::deque<int>& deq, int value, size_t left, size_t right)
{
	while (left <= right)
	{
		size_t mid = left + (right - left) / 2;

		if (deq[mid] < value)
			left = mid + 1;
		else
		{
			if (mid == 0)
				break;
			right = mid - 1;
		}
	}
	return left;
}

void PmergeMe::fordJohnsonSort(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;

	bool hasOdd = (vec.size() % 2 != 0);
	int odd = -1;

	if (hasOdd)
	{
		odd = vec.back();
		vec.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < vec.size(); i += 2)
	{
		vecComparisons++;
		if (vec[i] > vec[i+1])
			pairs.push_back(std::make_pair(vec[i], vec[i+1]));
		else
			pairs.push_back(std::make_pair(vec[i+1], vec[i]));
	}

	std::vector<int> larger;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger.push_back(pairs[i].first);

	fordJohnsonSort(larger);

	// Create mapping from winner to pend element
	std::map<int, int> winnerToPend;
	for (size_t i = 0; i < pairs.size(); ++i)
		winnerToPend[pairs[i].first] = pairs[i].second;

	std::vector<int> pend_sorted;
	for (size_t i = 0; i < larger.size(); ++i)
		pend_sorted.push_back(winnerToPend[larger[i]]);

	std::vector<int> mainChain = larger;
	std::vector<size_t> partnerPos(pairs.size());
	for (size_t i = 0; i < larger.size(); ++i)
		partnerPos[i] = i;

	// Insert first pend element at front (0 comparisons)
	if (!pend_sorted.empty())
	{
		mainChain.insert(mainChain.begin(), pend_sorted[0]);
		for (size_t i = 0; i < partnerPos.size(); ++i)
			partnerPos[i]++; // Shift positions after front insertion
	}

	// Insert remaining pend elements using Jacobsthal order
	if (pend_sorted.size() > 1)
	{
		std::vector<size_t> insertionOrder = generateInsertionOrder(pend_sorted.size());
		for (size_t i = 0; i < insertionOrder.size(); ++i)
		{
			size_t idx = insertionOrder[i];
			if (idx == 0)
				continue; // Skip first (already inserted)
			if (idx >= pend_sorted.size())
				continue;

			int val = pend_sorted[idx];
			size_t currentPartnerPos = partnerPos[idx];
			size_t searchEnd;

			if (currentPartnerPos > 0)
				searchEnd = currentPartnerPos - 1;
			else
				searchEnd = 0;

			size_t insertPos = binarySearch(mainChain, val, 0, searchEnd);
			mainChain.insert(mainChain.begin() + insertPos, val);

			// Update partner positions after insertion
			for (size_t j = 0; j < partnerPos.size(); ++j)
				if (partnerPos[j] >= insertPos)
					partnerPos[j]++;
		}
	}

	// Insert odd if exists
	if (hasOdd)
	{
		size_t pos = binarySearch(mainChain, odd, 0, mainChain.size() - 1);
		mainChain.insert(mainChain.begin() + pos, odd);
	}

	vec = mainChain;
}


void PmergeMe::fordJohnsonSort(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return;

	bool hasOdd = (deq.size() % 2 != 0);
	int odd = -1;

	if (hasOdd)
	{
		odd = deq.back();
		deq.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < deq.size(); i += 2)
	{
		if (deq[i] > deq[i+1])
			pairs.push_back(std::make_pair(deq[i], deq[i+1]));
		else
			pairs.push_back(std::make_pair(deq[i+1], deq[i]));
	}

	std::deque<int> larger;
	for (size_t i = 0; i < pairs.size(); ++i)
		larger.push_back(pairs[i].first);

	fordJohnsonSort(larger);

	std::map<int, int> winnerToPend;
	for (size_t i = 0; i < pairs.size(); ++i)
		winnerToPend[pairs[i].first] = pairs[i].second;

	std::deque<int> pend_sorted;
	for (size_t i = 0; i < larger.size(); ++i)
		pend_sorted.push_back(winnerToPend[larger[i]]);

	std::deque<int> mainChain = larger;
	std::vector<size_t> partnerPos(pairs.size());
	for (size_t i = 0; i < larger.size(); ++i)
		partnerPos[i] = i;

	if (!pend_sorted.empty())
	{
		mainChain.push_front(pend_sorted[0]);
		for (size_t i = 0; i < partnerPos.size(); ++i)
			partnerPos[i]++;
	}

	if (pend_sorted.size() > 1)
	{
		std::vector<size_t> insertionOrder = generateInsertionOrder(pend_sorted.size());
		for (size_t i = 0; i < insertionOrder.size(); ++i)
		{
			size_t idx = insertionOrder[i];
			if (idx == 0)
				continue;
			if (idx >= pend_sorted.size())
				continue;

			int val = pend_sorted[idx];
			size_t currentPartnerPos = partnerPos[idx];
			size_t searchEnd;

			if (currentPartnerPos > 0)
				searchEnd = currentPartnerPos - 1;
			else
				searchEnd = 0;

			size_t insertPos = binarySearch(mainChain, val, 0, searchEnd);
			mainChain.insert(mainChain.begin() + insertPos, val);

			for (size_t j = 0; j < partnerPos.size(); ++j)
				if (partnerPos[j] >= insertPos)
					partnerPos[j]++;
		}
	}

	if (hasOdd)
	{
		size_t pos = binarySearch(mainChain, odd, 0, mainChain.size() - 1);
		mainChain.insert(mainChain.begin() + pos, odd);
	}
	
	deq = mainChain;
}


bool PmergeMe::isPositiveInteger(const std::string& s) const
{
	if (s.empty())
		return false;

	for (size_t i = 0; i < s.size(); ++i)
		if (!isdigit(s[i]))
			return false;

	return true;
}

void PmergeMe::printContainer(const std::vector<int>& vec) const
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i];
		if (i + 1 < vec.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::printContainer(const std::deque<int>& deq) const
{
	for (size_t i = 0; i < deq.size(); ++i)
	{
		std::cout << deq[i];
		if (i + 1 < deq.size())
			std::cout << " ";
	}
	std::cout << std::endl;
}