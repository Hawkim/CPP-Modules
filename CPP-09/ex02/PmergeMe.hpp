#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <cstddef>

class PmergeMe {
public:
    PmergeMe();
    ~PmergeMe();

    // Sort + count comparisons (incremented only on key comparisons)
    void sort_vec (std::vector<int>& v, std::size_t& comps);
    void sort_deque(std::deque<int>& d,  std::size_t& comps);

    // Simple printers
    void print_vector(const std::vector<int>& v) const;
    void print_deque (const std::deque<int>& d) const;

private:
    // ---- Internal helpers (vector) ----
    static void pairwise_swap_vec(std::vector<int>& v, std::size_t& comps);
    static int  lower_bound_count_vec(const std::vector<int>& a, int key, int hi, std::size_t& comps);
    static int  find_index_vec(const std::vector<int>& v, int value);
    static int  find_paired_first_vec(const std::vector< std::pair<int,int> >& pairs, int first);
    static int  find_paired_second_vec(const std::vector< std::pair<int,int> >& pairs, int second);
    static std::vector<int> arrange_losers_vec(const std::vector< std::pair<int,int> >& main_pairs,
                                               const std::vector<int>& winners,
                                               int odd);

    // ---- Internal helpers (deque) ----
    static void pairwise_swap_deq(std::deque<int>& d, std::size_t& comps);
    static int  lower_bound_count_deq(const std::deque<int>& a, int key, int hi, std::size_t& comps);
    static int  find_index_deq(const std::deque<int>& d, int value);
    static int  find_paired_first_deq(const std::deque< std::pair<int,int> >& pairs, int first);
    static int  find_paired_second_deq(const std::deque< std::pair<int,int> >& pairs, int second);
    static std::deque<int> arrange_losers_deq(const std::deque< std::pair<int,int> >& main_pairs,
                                              const std::deque<int>& winners,
                                              int odd);

    // Jacobsthal-guided insertion order (no sets/finds; linear-time build)
    static void build_jacobsthal_insertion_order(std::vector<int>& order, std::size_t n);
};

#endif // PMERGEME_HPP
