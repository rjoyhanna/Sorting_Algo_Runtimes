#include "json.hpp"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {
   ifstream firstFile;
   firstFile.open(argv[1]);
   nlohmann::json firstObject;

   ifstream scndFile;
   scndFile.open(argv[2]);
   nlohmann::json scndObject;

   if (firstFile.is_open() && scndFile.is_open()) {
      firstFile >> firstObject;
      scndFile >> scndObject;
   }
   else {
      cout << "Something went wrong" << endl;
      return 1;
   }
   int arraySize = firstObject["metadata"]["arraySize"];

   int samplesWithConflictingResults = 0;
   cout << "{";

   //finding mistmatches per sample
   for (auto itr = firstObject.begin(); itr != firstObject.end() && itr.key() != "metadata"; itr++) {
      int numMismatches = 0;
      for (int i=0; i < arraySize; i++) {
         if (itr.value()[i] != scndObject[itr.key()][i]) {
            numMismatches +=1;
            if (numMismatches == 1) {
               cout << "\"" << itr.key() << "\":{\"Mismatches\":{";
               cout << "\"" << numMismatches-1 << "\":[" << itr.value()[i] << "," << scndObject[itr.key()][i] << "]";
               samplesWithConflictingResults +=1;
            }
            else {
               cout << ",\"" << numMismatches-1 << "\":[" << itr.value()[i] << "," << scndObject[itr.key()][i] << "]";
            }
         }
      }
      if (numMismatches != 0) {
            cout << "},";
            cout << "\"sample1\":" << itr.value() << ",";
            cout << "\"sample2\":" << scndObject[itr.key()] << "},";
      }
   }

   //print out metadata
   cout << "\"metadata\":{\"samplesWithConflictingResults\":" << samplesWithConflictingResults << "},";
   cout <<  "\"sample1\":{\"metadata\":{\"arraySize\":" << firstObject["metadata"]["arraySize"] << ",";
   cout << "\"file\":\"" << argv[1] << "\",\"numSamples\":" << firstObject["metadata"]["numSamples"] << "}},";
   cout <<  "\"sample2\":{\"metadata\":{\"arraySize\":" << scndObject["metadata"]["arraySize"] << ",";
   cout << "\"file\":\"" << argv[2] << "\",\"numSamples\":" << scndObject["metadata"]["numSamples"] << "}}";

   cout << "}";
   return 0;
}