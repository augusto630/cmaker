#include "string_helper.h"

#include <string>
#include <tuple>
#include <vector>

#include "test_cases.h"
#include "gtest/gtest.h"

std::atomic<size_t> g_allocated_count{0};
std::atomic<size_t> g_free_count{0};

void *operator new(std::size_t size) {
    g_allocated_count++;
    return std::malloc(size);
}

void operator delete(void *ptr) noexcept {
    g_free_count++;
    std::free(ptr);
}

const auto startsWith_TestCases = std::vector<std::tuple<std::string, std::string, bool> >{
    {"abc", "abc", true},
    {"abc", "ab", true},
    {"abc", "bc", false},
    {"abc", "a", true},
    {"abc", "b", false},
    {"", "abc", false},
    {"a", "A", false},
    {"A", "A", true},
    {"   abc", "   ", true},
    {"abc   ", "abc", true},
    {"abc   ", "abc ", true},
    {"xyz", "x", true},
    {"xyz", "y", false},
    {"xyz", "z", false},
    {"z", "zyes", false},
    {"longstringexample", "long", true},
    {"longstringexample", "string", false},
    {"123abc", "123", true},
    {"123abc", "abc", false},
    {"!@#", "!", true},
    {"!@#", "@", false},
};
TEST_WITH_CASES(startsWith, startsWith_should_return_expected_value, startsWith_TestCases) {
    // Arrange
    const auto [str, prefix, expected] = GetParam();

    // Act
    const bool result = stde::string::startsWith(str, prefix);

    // Assert
    ASSERT_EQ(result, expected);
}

const auto endsWith_TestCases = std::vector<std::tuple<std::string, std::string, bool> >{
    {"a", "b", false},
    {"a", "a", true},
    {"abcde", "a", false},
    {"a", "abcd", false},
    {"abcde", "d", false},
    {"abcde", "abcd", false},
    {"abcde", "bcde", true},
    {"abcde", "abcde", true},
    {"abcde", "e", true},
    {"abcde ", " ", true},
    {" abcde ", " ", true},
    {" abcde", " ", false},
    {"", "a", false},
    {"a", "", true},
    {"", "", true},
    {"abc", "c", true},
    {"abc", "b", false},
    {"abc", "abc", true},
    {"abc", "ab", false},
    {"abc", "bc", true},
    {"", "abc", false},
    {"a", "A", false},
    {"A", "A", true},
    {"   abc", "abc", true},
    {"abc   ", "   ", true},
    {"abc   ", "abc ", false},
    {"xyz", "z", true},
    {"xyz", "x", false},
    {"longstringexample", "example", true},
    {"longstringexample", "long", false},
    {"123abc", "123", false},
    {"123abc", "abc", true},
    {"!@#", "#", true},
    {"!@#", "!", false}
};
TEST_WITH_CASES(endsWith, endsWith_should_return_expected_value, endsWith_TestCases) {
    // Arrange
    const auto [str, prefix, expected] = GetParam();

    // Act
    const bool result = stde::string::endsWith(str, prefix);

    // Assert
    ASSERT_EQ(result, expected);
}

const auto splitArgs_TestCases = std::vector<std::tuple<std::string, std::string, std::vector<std::string> > >{
    {"test,one,two,three,four", ",", {"test", "one", "two", "three", "four"}},
    {"test,one,two,three,four,,,five", ",", {"test", "one", "two", "three", "four", "", "", "five"}},
    {"test,one", "", {"test,one"}},
    {"test,one", "+", {"test,one"}},
    {",test,one", ",", {"", "test", "one"}},
    {"", ",", {""}},
    {"", "", {""}},
    {"a", "", {"a"}},
    {"a", "a", {"", ""}},
    {"aa", "a", {"", "", ""}},
    {"a,b,c", ",", {"a", "b", "c"}},
    {"a,,b", ",", {"a", "", "b"}},
    {"a,b,", ",", {"a", "b", ""}},
    {",,", ",", {"", "", ""}},
    {"a--b--c", "--", {"a", "b", "c"}},
    {"aacaa", "aa", {"", "c", ""}},
    {" a b ", " ", {"", "a", "b", ""}},
    {"a b c", " ", {"a", "b", "c"}},
    {"a--b--c--", "--", {"a", "b", "c", ""}},
    {"--a--b--c", "--", {"", "a", "b", "c"}},
    {"abc", "z", {"abc"}},
    {"abc", "abc", {"", ""}},
    {"abcabcabc", "abc", {"", "", "", ""}},
    {"abcabcabc", "b", {"a", "ca", "ca", "c"}},
    {"123-456-789", "-", {"123", "456", "789"}},
    {"--", "--", {"", ""}},
    {"-a-b-", "-", {"", "a", "b", ""}},
    {"foo", "foo", {"", ""}},
    {"foobarfoo", "foo", {"", "bar", ""}},
    {"", "nonempty", {""}},
    {"repeat repeat repeat", " ", {"repeat", "repeat", "repeat"}},
    {"x,,y,,z", ",,", {"x", "y", "z"}},
    {"a,b,c,d", ",", {"a", "b", "c", "d"}},
    {"a;b;c;d", ";", {"a", "b", "c", "d"}},
    {"one|two|three", "|", {"one", "two", "three"}},
    {"multiple   spaces", " ", {"multiple", "", "", "spaces"}},
    {"abc\nxyz\n123", "\n", {"abc", "xyz", "123"}},
    {"abc\nxyz\n123\n", "\n", {"abc", "xyz", "123", ""}},
    {"abc", "abcd", {"abc"}},
};
TEST_WITH_CASES(split, endsWith_should_return_expected_value, splitArgs_TestCases) {
    // Arrange
    const auto [str, delim, expected] = GetParam();

    // Act
    const auto result = stde::string::split(str, delim);

    // Assert
    ASSERT_EQ(result, expected);
}

const auto alloc_TestCases = std::vector<std::tuple<std::string, std::string, int> >{
    {"", ",", 1},
    {",", ",", 2},
    {"a,b,c", ",", 3},
    {"abc", ",", 1},
    {"", ",", 1},
    {"abcdef", "bcde", 2},
};
TEST_WITH_CASES(split_allocations, split_allocations_should_be_minimal_and_not_leak, alloc_TestCases) {
    // Arrange
    const auto [str, delim, expected] = GetParam();
    g_allocated_count = 0;
    g_free_count = 0;

    // Act
    {
        const auto result = stde::string::split(str, delim);
    }

    const auto alloc_count = g_allocated_count.load();
    const auto free_count = g_free_count.load();

    // Assert
    ASSERT_EQ(alloc_count, free_count);
    ASSERT_EQ(alloc_count, expected);
}
