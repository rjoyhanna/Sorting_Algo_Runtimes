#include <iostream>
#include <fstream>
#include <ctime>
#include "json.hpp"
#include "insertionsort.h"
#include "quicksort.h"
#include "mergesort.h"
using namespace std;

int main(int argc, char** argv) {
    ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if (file.is_open()) {
        file >> jsonObject;
    }
    else {
        cout << "Error" << endl;
        return 1;
    }
    cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess," << 
            "MergeSortTime,MergeSortCompares,MergeSortMemaccess," <<
            "QuickSortTime,QuickSortCompares,QuickSortMemaccess" << endl;

    for (auto itr = jsonObject.begin(); itr!=jsonObject.end() && itr.key() != "metadata"; itr++) {
        cout << itr.key() << ",";
        std::vector<int> insertArr, mergeArr, quickArr;
        for (int i = 0; i < jsonObject["metadata"]["arraySize"]; ++i) {
            insertArr.push_back(itr.value()[i]);
            mergeArr.push_back(itr.value()[i]);
            quickArr.push_back(itr.value()[i]);
        }

        int InsertionSortTime, InsertionSortMemaccess, InsertionSortCompares;
        InsertionSortTime = InsertionSortMemaccess = InsertionSortCompares = 0;
        int MergeSortTime, MergeSortMemaccess, MergeSortCompares;
        MergeSortTime = MergeSortMemaccess = MergeSortCompares = 0;
        int QuickSortTime, QuickSortMemaccess, QuickSortCompares;
        QuickSortTime = QuickSortMemaccess = QuickSortCompares = 0;
        clock_t time = clock();
        InsertionSort(&insertArr, &InsertionSortMemaccess, &InsertionSortCompares);
        InsertionSortTime = clock() - time;
        time = clock();
        MergeSort(&mergeArr, &MergeSortMemaccess, &MergeSortCompares);
        MergeSortTime = clock() - time;
        time = clock();
        QuickSort(&quickArr, &QuickSortMemaccess, &QuickSortCompares);
        QuickSortTime = clock() - time;

        cout << ((double)InsertionSortTime)/CLOCKS_PER_SEC<< "," << InsertionSortCompares<< "," << InsertionSortMemaccess<< ",";
        cout << ((double)MergeSortTime)/CLOCKS_PER_SEC<< ","<< MergeSortCompares << "," << MergeSortMemaccess << ",";
        cout << ((double)QuickSortTime)/CLOCKS_PER_SEC<< "," << QuickSortCompares << "," << QuickSortMemaccess;
        cout << endl;
    }


    return 0;
}