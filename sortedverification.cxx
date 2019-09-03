#include <iostream>
#include <fstream>
#include "json.hpp"
using namespace std;

int main(int argc, char** argv) {
    ifstream file;
    file.open(argv[1]);
    nlohmann::json jsonObject;
    if(file.is_open()) {
        file >> jsonObject;
    }
    else {
        cout << "Something went wrong, try with a different file name?" << endl;
        return 1;
    }

    int samplesWithInversions = 0;

    cout << "{";
    for (auto itr = jsonObject.begin(); itr != jsonObject.end() && itr.key() != "metadata"; itr++) {
        bool hasInversion = false;
        int lastVal = itr.value()[0];
        int index = 0;
        for (auto arrItr = itr.value().begin(); arrItr != itr.value().end(); arrItr++) {
            if (*arrItr < lastVal) {
                if (!hasInversion) { //if it hasn't already found inversions (changes behavior for first inversion)
                    cout << "\"" << itr.key() << "\":{\"ConsecutiveInversions\":{" ;
                    cout << "\"" << index-1 << "\":[" << lastVal << "," << *arrItr << "]";
                    hasInversion = true;
                    samplesWithInversions +=1;
                }
                else {
                    cout << ",\"" << index-1 << "\":[" << lastVal << "," << *arrItr << "]";
                }
            }
            index += 1;
            lastVal = *arrItr;
        }
        if (hasInversion) { //for a sample with an inversion, close the open bracket
            cout << "},\"sample\":";
            cout << itr.value() ;
            cout << "},";
        }
    }

    cout << "\"metadata\":{\"arraySize\":" << jsonObject["metadata"]["arraySize"] << ",\"file\":\"" << argv[1] << "\",";
    cout << "\"numSamples\":" << jsonObject["metadata"]["numSamples"] << ",\"samplesWithInversions\":" << samplesWithInversions << "}";

    cout << "}";
    return 0;
}