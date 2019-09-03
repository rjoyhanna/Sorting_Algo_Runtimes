// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector>

void QuickSort(std::vector<int>* numbers, int* memaccess, int* compares);
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int* memaccess, int* compares);
int Partition(std::vector<int>* numbers, int i, int k, int* memaccess, int* compares);