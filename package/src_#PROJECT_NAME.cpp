#include "#PROJECT_NAME.h"

#include <iostream>

#include "args.h"
#include "release_assert.h"

namespace #PROJECT_NAME {
    int main::run(int argc, const char **argv) {
        if (args.parseArgs(argc, argv) == false) {
            return 1;
        };

        assert(true, "Hello assert world");
        std::cout << "Hello regular world" << std::endl;
        return 0;
    }
}