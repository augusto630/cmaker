#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include "version.h"
#include "release_assert.h"

namespace #PROJECT_NAME {
    struct argsInfo {
        bool doSomething{};

        /**
         * parses arguments into a map of options and option args
         * for example:
         * @code
          ./myApp -a myArg -t -o otherArg1 otherArg2 otherArg3

          will result in the following map:

          -a : myArg
          -t : ""
          -o : otherArg1
          "" : otherArg2 otherArg3
         * @endcode
         * @param argc argument count
         * @param args argument pointer
         * @return whether to continue the application or not
         */
        bool parseArgs(const int argc, const char *const*args) {
            assert(argc == 0 || args != nullptr, "expected at least one value on args, but found nullptr");
            std::unordered_map<std::string, std::string> arguments{};

            std::string option{};
            for (int i = 1; i < argc; i++) {

                if (args[i][0] == '-') {
                    option = args[i];
                    arguments[option] = "";
                    continue;
                }

                arguments[option] += args[i];

                if (option.empty())
                    arguments[option] += " ";

                option.clear();
            }

            // prints current project name and version when -h o --help is passed
            if (arguments.count("-h") || arguments.count("--help")) {
                std::cout << "#PROJECT_NAME v" << version::semantic;
                return false;
            }

            // assigns doSomething to true when -d or --do-something is passed as an argument
            doSomething = arguments.count("-d") || arguments.count("--do-something");

            /*
             * add here handling or further options
             */

            return true;
        }
    };
}
