#pragma once
#include <embedded_package.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include "version.h"
#include "release_assert.h"
#include "string_helper.h"

namespace cmaker {
    struct argsInfo {
        bool quiet{};
        bool truncate{};
        bool dryRun{};
        std::string projectName{};

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

            if (arguments.count("-h") || arguments.count("--help")) {
                std::cout << "CMaker v" << version::semantic << "\n";
                std::cout << embedded::_usage_txt_sv << std::endl;
                return false;
            }

            projectName = arguments.count("-p") ? arguments["-p"] : projectName;
            projectName = arguments.count("--project") ? arguments["--project"] : projectName;
            projectName = projectName.empty() ? std::filesystem::current_path().filename().string() : projectName;
            projectName = stde::string::replace(std::string{projectName}, "-", "_");

            dryRun = arguments.count("-d") || arguments.count("--dry");
            quiet = arguments.count("-q") || arguments.count("--quiet");
            truncate = arguments.count("-t") || arguments.count("--truncate");
            return true;
        }
    };
}
