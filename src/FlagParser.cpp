#include "FlagParser.h"

using std::string;

FlagParser::FlagParser(int argc, char **argv) : _args(argc) {
    for (int i = 0; i < argc; i++) {
        _args[i] = argv[i];
    }

    for (uint8_t i = 0; i < _args.size(); i++) {
        if (_args[i].find("--") != 0) {
            continue;
        }
        string::size_type eqIndex = _args[i].find("=");
        if (eqIndex == string::npos) {
            _flags[_args[i].substr(2)] = "error";
            _args.erase(_args.begin() + i--);
            continue;
        }
        auto optionName = _args[i].substr(2, eqIndex - 2);
        _flags[optionName] = _args[i].substr(eqIndex + 1);
        _args.erase(_args.begin() + i);
        --i;
    }
}

bool FlagParser::isSet(string flag) const {
    return _flags.find(flag) != _flags.end();
}

string FlagParser::getOption(string flag) const {
    return _flags.at(flag);
}

string FlagParser::getArg(uint32_t num) const {
    return _args[num];
}

int FlagParser::getNumArgs() const {
    return _args.size();
}
