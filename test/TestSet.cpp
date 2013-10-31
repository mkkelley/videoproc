#include "TestSet.h"

#include <iostream>

using std::cout;
using std::endl;
using std::function;
using std::string;

void TestSet::registerTest(function<bool()> fn, string name) {
    _testList.push_back(std::make_pair(fn, name));
}

bool TestSet::runTests() const {
    unsigned int numPassed = 0;
    unsigned int numFailed = 0;
    for (std::vector<function<bool()>>::size_type i = 0; i < _testList.size(); i++) {
        bool passed = _testList[i].first();
        if (passed) {
            ++numPassed;
            cout << "\t[PASSED] ";
        } else {
            ++numFailed;
            cout << "[FAILED] ";
        }
        cout << _testList[i].second << endl;
    }
    cout << endl << numPassed << " tests passed";
    cout << endl << numFailed << " tests failed" << endl;
    return numFailed == 0;
}