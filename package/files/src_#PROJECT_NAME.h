#pragma once
#include <vector>

namespace #PROJECT_NAME {
    class main {
        std::vector<std::string> args{};

    public:
        main(const int argc, const char **argv) {
            for (int i = 1; i < argc; i++) {
                args.push_back(argv[i]);
            }
        }

        int run();
    };
}