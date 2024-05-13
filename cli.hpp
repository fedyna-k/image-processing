#ifndef __CLI_HPP__
#define __CLI_HPP__

#include <string>
#include <unordered_map>
#include <vector>

/**
 * \brief The CLI API.
 */
namespace CLI {
    typedef std::unordered_map<std::string, bool> OptionMap;
    typedef std::vector<std::string> Args;

    std::string help_message = "Usage: pic [options] <path>\n"
                               "  -gs   Apply grayscale filter\n"
                               "  -gsl  Compute grayscale histogram on cliked line (currently only works with images)\n"
                               "  -gse  Compute grayscale expansion and given histograms\n"
                               "  -ed   Apply edge detection filter";

    /**
     * \brief Processes the options.
     * 
     * \param[in] argc The argument count.
     * \param[in] argv The arguments strings.
     * 
     * \returns All the arguments with boolean to say if they are given.
     */
    OptionMap processOptions(int argc, char **argv) {
        OptionMap keys = {{"-gs", false}, {"-gsl", false}, {"-gse", false}, {"-ed", false}};

        for (int i = 1 ; i < argc ; i++) {
            if (keys.find(argv[i]) != keys.end()) {
                keys[argv[i]] = true;
            }
        }

        return keys;
    }

    /**
     * \brief Processes the arguments.
     * 
     * \param[in] argc The argument count.
     * \param[in] argv The arguments strings.
     * 
     * \returns The argument list.
     */
    Args getArgs(int argc, char **argv) {
        OptionMap keys = {{"-gs", false}, {"-gsl", false}, {"-gse", false}, {"-ed", false}};
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