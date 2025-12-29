#include "#PROJECT_NAME.h"

#include <string>
#include <array>
#include <iterator>
#include <tuple>
#include <vector>

#include "string_helper.h"
#include "test_cases.h"
#include "gtest/gtest.h"

TEST(main, main_should_return_0) {
    // Arrange
    #PROJECT_NAME::main main{};

    // Act
    int result = main.run(0, nullptr);

    // Assert
    ASSERT_EQ(result, 0);
}

///
/// This test is not necessary but serves to illustrate how to work with test cases
///
std::vector<std::tuple<std::string, int> > exitCode_TestCases{
        {"./", 0},
        {"./ -h", 0},
    };
TEST_WITH_CASES(exitCode, main_should_exit_with_expected_code, exitCode_TestCases) {
    // Arrange
    const auto [args, expected] = GetParam();

    // Act
    // ... Add logic here

    // Assert
    ASSERT_EQ(0, expected);
}
