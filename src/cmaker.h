#pragma once
#include <complex>
#include <filesystem>
#include <iostream>
#include <unordered_set>
#include <vector>

namespace cmaker {
    struct args {
        bool quiet{};
        bool truncate{};
        bool dryRun{};
        std::string projectName{};

        bool parseArgs(const int argc, const char **argv) {
            std::unordered_map<std::string, std::string> arguments{};
            for (int i = 1; i < argc; i++) {
                if (i + 1 < argc)
                    arguments[argv[i]] = argv[i + 1];
                else
                    arguments[argv[i]] = "";
            }

            if (arguments.count("-h") || arguments.count("--help")) {
                std::cout << "Usage: cmaker [Options] [Arg]\n";
                std::cout << "\n";
                std::cout << "Options: [-h|--help] print this help\n";
                std::cout << "         [-t|--truncate] truncates existing files\n";
                std::cout << "         [-d|--dry] executes a dry-run\n";
                std::cout <<
                        "         [-p|--project] [Arg] specifies the project name, if omitted, the current directory will be used instead \n";
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

    inline args args;

    template<typename... T>
    void print(T &... t) {
        if (args.quiet)
            return;

        // ((expr)...) fold expansion, it recursively calls expr as long as there are ... to unpack
        ((std::cout << t), ...);
    }


    class main {
    public:
        static std::string replaceProjectName(const std::string &projectName, std::string_view content);

        static void write(const std::string &projectName, const std::string &dir, const std::string &file,
                          std::string_view content);

        [[nodiscard]] int run() const;
    };
}
