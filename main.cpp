#include <_stdlib.h>

#include "cmaker.h"

int main(const int argc, const char * const*argv) {
    return cmaker::main{}.run(argc, argv);
}
