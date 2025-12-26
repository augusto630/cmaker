#include <gtest/gtest.h>

TEST(cmaker, my_test_case) {
    // Arrange
    const auto a = 1;
    const auto b = 1;

    // Act
    const auto c = a + b;

    // Assert
    ASSERT_EQ(3, c);
}
