#include "PmergeMe.hpp"

#include <algorithm>
#include <iostream>

// =========================
// Public API
// =========================
PmergeMe::PmergeMe() {}
PmergeMe::~PmergeMe() {}

void PmergeMe::print_vector(const std::vector<int>& v) const {
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) std::cout << " ";
        std::cout << v[i];
    }
    std::cout << std::endl;
}

void PmergeMe::print_deque(const std::deque<int>& d) const {
    for (std::size_t i = 0; i < d.size(); ++i) {
        if (i) std::cout << " ";
        std::cout << d[i];
    }
    std::cout << std::endl;
}

// =========================
// Jacobsthal order (shared)
// =========================
static unsigned jac_next(unsigned a, unsigned b) { return a + 2u*b; } // J(n)=J(n-1)+2J(n-2)

void PmergeMe::build_jacobsthal_insertion_order(std::vector<int>& order, std::size_t n) {
    order.clear();
    if (n == 0) return;
    order.push_back(0);               // always insert pending[0] first
    if (n == 1) return;

    // Build Jacobsthal sequence: 0,1,1,3,5,11,... until >= n
    std::vector<unsigned> J; J.reserve(32);
    J.push_back(0u); J.push_back(1u);
    while (J.back() < n) {
        unsigned next = jac_next(J[J.size()-1], J[J.size()-2]);
        J.push_back(next);
    }

    // Push ranges (prev+1 .. cur-1) in DESC order, then fill remaining ASC
    std::vector<char> seen(n, 0);
    seen[0] = 1;

    unsigned prev = 1u;
    for (std::size_t k = 2; k < J.size(); ++k) {
        unsigned cur = J[k];
        int start = (int)prev + 1;
        int end   = (int)cur  - 1;
        for (int i = end; i >= start; --i) {
            if (i >= 0 && (std::size_t)i < n && !seen[i]) {
                order.push_back(i);
                seen[i] = 1;
            }
        }
        prev = cur;
        if (cur >= n) break;
    }
    for (std::size_t i = 0; i < n; ++i) {
        if (!seen[i]) { order.push_back((int)i); seen[i] = 1; }
    }
}

// =========================
// Vector helpers
// =========================
void PmergeMe::pairwise_swap_vec(std::vector<int>& v, std::size_t& comps) {
    for (std::size_t i = 0; i + 1 < v.size(); i += 2) {
        ++comps; // compare v[i] > v[i+1]
        if (v[i] > v[i+1]) std::swap(v[i], v[i+1]);
    }
}

int PmergeMe::lower_bound_count_vec(const std::vector<int>& a, int key, int hi, std::size_t& comps) {
    if (a.empty()) return 0;
    int lo = 0;
    if (hi >= (int)a.size()) hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        ++comps;                       // one key comparison per step
        if (a[mid] < key) lo = mid + 1;
        else               hi = mid - 1;
    }
    return lo; // insertion position
}

int PmergeMe::find_index_vec(const std::vector<int>& v, int value) {
    for (std::size_t i = 0; i < v.size(); ++i) if (v[i] == value) return (int)i;
    return -1;
}

int PmergeMe::find_paired_first_vec(const std::vector< std::pair<int,int> >& pairs, int first) {
    for (std::size_t i = 0; i < pairs.size(); ++i) if (pairs[i].first == first) return pairs[i].second;
    return -1;
}

int PmergeMe::find_paired_second_vec(const std::vector< std::pair<int,int> >& pairs, int second) {
    for (std::size_t i = 0; i < pairs.size(); ++i) if (pairs[i].second == second) return pairs[i].first;
    return -1;
}

std::vector<int> PmergeMe::arrange_losers_vec(const std::vector< std::pair<int,int> >& main_pairs,
                                              const std::vector<int>& winners,
                                              int odd)
{
    std::vector<int> losers; losers.reserve(winners.size() + (odd!=-1));
    for (std::size_t i = 0; i < winners.size(); ++i) {
        int w = winners[i];
        int l = find_paired_first_vec(main_pairs, w); // loser paired to this winner
        if (l != -1) losers.push_back(l);
    }
    if (odd != -1) losers.push_back(odd);
    return losers;
}

// =========================
// Deque helpers
// =========================
void PmergeMe::pairwise_swap_deq(std::deque<int>& d, std::size_t& comps) {
    for (std::size_t i = 0; i + 1 < d.size(); i += 2) {
        ++comps; // compare d[i] > d[i+1]
        if (d[i] > d[i+1]) std::swap(d[i], d[i+1]);
    }
}

int PmergeMe::lower_bound_count_deq(const std::deque<int>& a, int key, int hi, std::size_t& comps) {
    if (a.empty()) return 0;
    int lo = 0;
    if (hi >= (int)a.size()) hi = (int)a.size() - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        ++comps;                       // one key comparison per step
        if (a[mid] < key) lo = mid + 1;
        else               hi = mid - 1;
    }
    return lo; // insertion position
}

int PmergeMe::find_index_deq(const std::deque<int>& d, int value) {
    for (std::size_t i = 0; i < d.size(); ++i) if (d[i] == value) return (int)i;
    return -1;
}

int PmergeMe::find_paired_first_deq(const std::deque< std::pair<int,int> >& pairs, int first) {
    for (std::size_t i = 0; i < pairs.size(); ++i) if (pairs[i].first == first) return pairs[i].second;
    return -1;
}

int PmergeMe::find_paired_second_deq(const std::deque< std::pair<int,int> >& pairs, int second) {
    for (std::size_t i = 0; i < pairs.size(); ++i) if (pairs[i].second == second) return pairs[i].first;
    return -1;
}

std::deque<int> PmergeMe::arrange_losers_deq(const std::deque< std::pair<int,int> >& main_pairs,
                                             const std::deque<int>& winners,
                                             int odd)
{
    std::deque<int> losers;
    for (std::size_t i = 0; i < winners.size(); ++i) {
        int w = winners[i];
        int l = find_paired_first_deq(main_pairs, w);
        if (l != -1) losers.push_back(l);
    }
    if (odd != -1) losers.push_back(odd);
    return losers;
}

// =========================
// Core algorithms
// =========================
void PmergeMe::sort_vec(std::vector<int>& v, std::size_t& comps) {
    if (v.size() <= 1) return;

    // 1) Order each adjacent pair and build (winner, loser)
    pairwise_swap_vec(v, comps);
    std::vector< std::pair<int,int> > pairs;
    pairs.reserve(v.size()/2);
    int odd = -1;

    for (std::size_t i = 0; i < v.size(); i += 2) {
        if (i + 1 < v.size()) {
            pairs.push_back(std::make_pair(v[i+1], v[i])); // (winner, loser)
        } else {
            odd = v[i];
        }
    }

    // 2) Split winners (main chain to be sorted) and derive losers in same winner order
    std::vector<int> winners;
    winners.reserve((v.size()+1)/2);
    
    for (std::size_t i = 0; i < pairs.size(); ++i) winners.push_back(pairs[i].first);

    sort_vec(winners, comps); // recursively sort winners

    std::vector<int> losers = arrange_losers_vec(pairs, winners, odd);

    // 3) Insertion order for losers
    std::vector<int> order; order.reserve(losers.size());
    build_jacobsthal_insertion_order(order, losers.size());

    // Pre-insert first loser if present and more than one to insert (classic optimization)
    if (order.size() > 1 && !losers.empty()) {
        winners.insert(winners.begin(), losers[0]);
        losers[0] = -1; // mark consumed
    }

    // 4) Insert remaining losers using bounded binary search
    for (std::size_t k = 0; k < order.size(); ++k) {
        int idx = order[k];
        if (idx < 0 || (std::size_t)idx >= losers.size()) continue;

        int val = losers[idx];
        if (val == -1) continue;

        int win_partner = find_paired_second_vec(pairs, val); // winner paired to this loser
        int hi = find_index_vec(winners, win_partner) - 1;    // search strictly before partner
        if (hi < 0) {
            winners.insert(winners.begin(), val);
        } else {
            int pos = lower_bound_count_vec(winners, val, hi, comps);
            winners.insert(winners.begin() + pos, val);
        }
    }

    v.swap(winners);
}

void PmergeMe::sort_deque(std::deque<int>& d, std::size_t& comps) {
    if (d.size() <= 1) return;

    // 1) Order each adjacent pair and build (winner, loser)
    pairwise_swap_deq(d, comps);
    std::deque< std::pair<int,int> > pairs;
    int odd = -1;

    for (std::size_t i = 0; i < d.size(); i += 2) {
        if (i + 1 < d.size()) {
            pairs.push_back(std::make_pair(d[i+1], d[i])); // (winner, loser)
        } else {
            odd = d[i];
        }
    }

    // 2) Split winners (main chain) and losers aligned to winners
    std::deque<int> winners;
    for (std::size_t i = 0; i < pairs.size(); ++i) winners.push_back(pairs[i].first);

    sort_deque(winners, comps); // recursively sort winners

    std::deque<int> losers = arrange_losers_deq(pairs, winners, odd);

    // 3) Insertion order
    std::vector<int> order; order.reserve(losers.size());
    build_jacobsthal_insertion_order(order, losers.size());

    if (order.size() > 1 && !losers.empty()) {
        winners.insert(winners.begin(), losers[0]);
        losers[0] = -1;
    }

    // 4) Insert remaining losers using bounded binary search
    for (std::size_t k = 0; k < order.size(); ++k) {
        int idx = order[k];
        if (idx < 0 || (std::size_t)idx >= losers.size()) continue;

        int val = losers[idx];
        if (val == -1) continue;

        int win_partner = find_paired_second_deq(pairs, val);
        int hi = find_index_deq(winners, win_partner) - 1;
        if (hi < 0) {
            winners.insert(winners.begin(), val);
        } else {
            int pos = lower_bound_count_deq(winners, val, hi, comps);
            winners.insert(winners.begin() + pos, val);
        }
    }

    d.swap(winners);
}
