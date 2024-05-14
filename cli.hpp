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

    std::string help_message = "\x1b[1mUsage\x1b[0m: pia [option|...parameters] <path>\n\n"
                               "\x1b[1mOptions\x1b[0m:\n"
                               "  --help     Displays this message\n"
                               "  --version  Displays the version message\n\n"
                               "\x1b[1mParameters\x1b[0m:\n"
                               "  \x1b[2mGrayscale\x1b[0m:\n"
                               "    -gs      Apply grayscale filter\n"
                               "    -gsl     Compute grayscale histogram on cliked line (currently only works with images)\n"
                               "    -gse     Compute grayscale expansion and given histograms\n"
                               "  \x1b[2mEdges\x1b[0m:\n"
                               "    -ed      Apply edge detection filter";

    std::string version_number = "pic - Image Analysis program by Kevin F.\n"
                                 "Version 1.0.0";

    OptionMap all_keys = {
        {"--help", false}, {"--version", false},
        {"-gs", false}, {"-gsl", false}, {"-gse", false},
        {"-ed", false}
    };

    /**
     * \brief Processes the options.
     * 
     * \param[in] argc The argument count.
     * \param[in] argv The arguments strings.
     * 
     * \returns All the arguments with boolean to say if they are given.
     */
    OptionMap processOptions(int argc, char **argv) {
        OptionMap keys = all_keys;

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
        OptionMap keys = all_keys;
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