#include "#PROJECT_NAME.h"

#include <iostream>

#include "release_assert.h"

namespace #PROJECT_NAME {
    int main::run() {
        assert(true, "Hello assert world");
        std::cout << "Hello regular world" << std::endl;
        return 0;
    }
}