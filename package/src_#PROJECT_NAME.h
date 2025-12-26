#pragma once
#include <vector>
#include <string>

namespace #PROJECT_NAME {
    class main {
        std::vector<std::string> args{};

    public:
        main(const int argc, const char **argv) {
            for (int i = 1; i < argc; i++) {
                args.emplace_back(argv[i]);
            }
        }

        int run();
    };
}