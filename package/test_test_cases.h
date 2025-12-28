#pragma once

/**
 * creates a parametrized test
 * @param TEST_SUITE test suite in which all args will be applied to
 * @param TEST_CASE test case name
 * @param PARAMS test cases to be evaluated
 */
#define TEST_WITH_CASES(TEST_SUITE, TEST_CASE, PARAMS)                \
namespace {                                                           \
    using paramsType = decltype(PARAMS)::value_type;                  \
    decltype(PARAMS) testCases_##TEST_SUITE = PARAMS;                 \
    class TEST_SUITE                                                  \
        : public ::testing::TestWithParam<paramsType> {               \
    };                                                                \
                                                                      \
    INSTANTIATE_TEST_SUITE_P(                                         \
        test_cases,                                                   \
        TEST_SUITE,                                                   \
        ::testing::ValuesIn(testCases_##TEST_SUITE));                 \
}                                                                     \
TEST_P(TEST_SUITE, TEST_CASE)