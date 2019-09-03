// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"


void QuickSort(std::vector<int>* numbers, int* memaccess, int* compares) {
   QuickSortRecurse(numbers, 0, numbers->size() - 1, memaccess, compares);
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int* memaccess, int* compares) {
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k, memaccess, compares);
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j, memaccess, compares);
   QuickSortRecurse(numbers, j + 1, k, memaccess, compares);
   
   return;
}

int Partition(std::vector<int>* numbers, int i, int k, int* memaccess, int* compares) {
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = (*numbers)[midpoint];
   (*memaccess) += 1;
   
   l = i;
   h = k;
   
   while (!done) {
      (*memaccess) += 2;
      (*compares) += 2;
      /* Increment l while numbers[l] < pivot */
      while ((*numbers)[l] < pivot) {
         (*memaccess) += 1;
         (*compares) += 1;
         ++l;
      }
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < (*numbers)[h]) {
         (*memaccess) += 1;
         (*compares) += 1;
         --h;
      }

      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = (*numbers)[l];
         (*numbers)[l] = (*numbers)[h];
         (*numbers)[h] = temp;
         (*memaccess) += 4;
         
         ++l;
         --h;
      }
   }
   
   return h;
}