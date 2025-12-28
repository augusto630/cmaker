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

TEST(main, help_should_return_1) {
    // Arrange
    #PROJECT_NAME::main main{};
    std::array<const char*, 2> args{"", "-h"};

    // Act
    int result = main.run(2, args.data());

    // Assert
    ASSERT_NE(result, 0);
}


///
/// This test is not necessary but serves to illustrate how to work with test cases
///
std::vector<std::tuple<std::string, int> > exitCode_TestCases{
        {"./", 0},
        {"./ -h", 1},
        {"./ --help", 1},
    };
TEST_WITH_CASES(exitCode, main_should_exit_with_expected_code, exitCode_TestCases) {
    // Arrange
    const auto [args, expected] = GetParam();
    const auto argv = stde::string::split(args, " ");
    const auto argc = std::size(argv);
    #PROJECT_NAME::main main{};

    std::vector<const char *> ptrArgv{};
    ptrArgv.reserve(argv.size());

    for (const auto &arg: argv) {
        ptrArgv.push_back(arg.c_str());
    }

    // Act
    const auto result = main.run(std::size(ptrArgv), ptrArgv.data());

    // Assert
    ASSERT_EQ(result, expected);
}
