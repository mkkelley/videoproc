#pragma once

#include <vector>
#include <map>
#include <string>

class FlagParser {
    public:
        FlagParser(int argc, char **argv);
        bool isSet(std::string flag) const;
        std::string getOption(std::string flag) const;
        std::string getArg(uint32_t num) const;
        int getNumArgs() const;
    private:
        std::vector<std::string> _args;
        std::map<std::string, std::string> _flags;
};
