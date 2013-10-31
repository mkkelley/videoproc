#pragma once

#include <functional>
#include <string>
#include <vector>

class TestSet {
    public:
        void registerTest(std::function<bool()>, std::string);
        bool runTests() const;
    private:
        std::vector<
            std::pair<std::function<bool()>, std::string>
        > _testList;
};
