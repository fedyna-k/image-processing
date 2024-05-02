#ifndef __CLI_HPP__
#define __CLI_HPP__

#include <string>
#include <unordered_map>
#include <vector>

namespace CLI {
    typedef std::unordered_map<std::string, bool> OptionMap;
    typedef std::vector<std::string> Args;

    std::string help_message = "Usage: pic [options] <path>\n"
                               "  -gs   Apply grayscale filter\n"
                               "  -ed   Apply edge detection filter";

    OptionMap processOptions(int argc, char **argv) {
        OptionMap keys = {{"-gs", false}, {"-ed", false}};

        for (int i = 1 ; i < argc ; i++) {
            if (keys.find(argv[i]) != keys.end()) {
                keys[argv[i]] = true;
            }
        }

        return keys;
    }

    Args getArgs(int argc, char **argv) {
        OptionMap keys = {{"-gs", false}, {"-ed", false}};
        Args args = Args();

        for (int i = 1 ; i < argc ; i++) {
            if (keys.find(argv[i]) == keys.end()) {
                args.push_back(argv[i]);
            }
        }

        return args;
    }
}

#endif