#pragma once
#include <embedded_package.h>
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <version.h>

namespace cmaker {
    struct argsInfo {
        bool quiet{};
        bool truncate{};
        bool dryRun{};
        std::string projectName{};

        bool parseArgs(const int argc, const char *const*args) {
            std::unordered_map<std::string, std::string> arguments{};
            for (int i = 1; i < argc; i++) {
                if (i + 1 < argc)
                    arguments[args[i]] = args[i + 1];
                else
                    arguments[args[i]] = "";
            }

            if (arguments.count("-h") || arguments.count("--help")) {
                std::cout << "CMaker v" << version::semantic << "\n";
                std::cout << embedded::_usage_txt_sv << std::endl;
                return false;
            }

            projectName = arguments.count("-p") ? arguments["-p"] : projectName;
            projectName = arguments.count("--project") ? arguments["--project"] : projectName;
            projectName = projectName.empty() ? std::filesystem::current_path().filename().string() : projectName;

            dryRun = arguments.count("-d") || arguments.count("--dry");
            quiet = arguments.count("-q") || arguments.count("--quiet");
            truncate = arguments.count("-t") || arguments.count("--truncate");
            return true;
        }
    };
}
