#include "#PROJECT_NAME.h"

#include <string>
#include <array>

#include "gtest/gtest.h"

TEST(#PROJECT_NAME, main_should_return_0) {
    // Arrange
    #PROJECT_NAME::main main{};

    // Act
    int result = main.run(0, nullptr);

    // Assert
    ASSERT_EQ(result, 0);
}

TEST(#PROJECT_NAME, help_should_return_1) {
    // Arrange
    test_cmaker::main main{};
    std::array<const char*, 2> args{"", "-h"};

    // Act
    int result = main.run(2, args.data());

    // Assert
    ASSERT_NE(result, 0);
}
