#include <cmaker.h>
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <tuple>

#include "string_helper.h"
#include "test_cases.h"
#include "gtest/gtest.h"

const auto exitCode_TestCases = std::vector<std::tuple<std::string, int> >{
    {"./ -d", 0},
    {"./ -d -t", 0},
    {"./ --dry --truncate", 0},
    {"./ -d --oohlookatme", 0},
    {"./ --dry", 0},
    {"./ -h", 1},
    {"./ --help", 1},
};

TEST_WITH_CASES(exitCode, main_should_exit_with_expected_code, exitCode_TestCases) {
    // Arrange
    const auto [args, expected] = GetParam();
    const auto argv = stde::string::split(args, " ");
    const auto argc = std::size(argv);
    cmaker::main main{};

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
