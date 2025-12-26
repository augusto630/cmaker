#include <_stdlib.h>  // for EXIT_FAILURE
#include "cmaker.h"

int main(const int argc, const char **args) {
    if (cmaker::args.parseArgs(argc, args) == false) {
        return EXIT_FAILURE;
    }

    return cmaker::main{}.run();
}
