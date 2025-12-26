#pragma once
#include <iostream>

#undef assert

/**
 * asserts that an expression evaluates to true
 *
 * note: the expression is evaluated on Debug and Release
 * @param expr expression to evaluate
 * @param msg reason when failed
 */
#define assert(expr, msg)                         \
if (!(expr)) {                                    \
    std::cerr << "Assertion failed: " #expr "\n"; \
    std::cerr << "         Because: " #msg "\n";  \
    std::cerr << "              On: " << __FILE_NAME__ << ":" << __LINE__<< "\n";  \
    abort();                                      \
}

#ifdef NDEBUG
#define debug_assert(expr, msg) assert(expr, msg)
#else
#define debug_assert(expr, msg)
#endif

