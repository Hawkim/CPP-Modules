#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <iostream>
#include <sys/time.h>

bool parseInput(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq);
void fordJohnsonSort(std::vector<int>& vec, int& comparisons);
void fordJohnsonSort(std::deque<int>& deq, int& comparisons);
void displayDuration(struct timeval& start, struct timeval& end);

#endif
