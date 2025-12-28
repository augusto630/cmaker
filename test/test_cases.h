#pragma once
#include <gtest/gtest.h>

/**
 * creates a parametrized test
 * @param TEST_SUITE test suite in which all args will be applied to
 * @param TEST_CASE test case name
 * @param PARAMS test cases to be evaluated
 */
#define TEST_WITH_CASES(TEST_SUITE, TEST_CASE, PARAMS)                \
namespace {                                                           \
    using paramsType_##TEST_SUITE = decltype(PARAMS)::value_type;     \
    class TEST_SUITE                                                  \
        : public ::testing::TestWithParam<paramsType_##TEST_SUITE> {  \
    };                                                                \
                                                                      \
    INSTANTIATE_TEST_SUITE_P(                                         \
        test_cases,                                                   \
        TEST_SUITE,                                                   \
        ::testing::ValuesIn(PARAMS));                 \
}                                                                     \
TEST_P(TEST_SUITE, TEST_CASE)