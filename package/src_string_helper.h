#pragma once
#include <stddef.h>
#include <regex>
#include <string>
#include <iterator>
#include <sstream>
#include <vector>

/**
 * standard library extended
 */
namespace stde {
    /**
     * string manipulation
     */
    namespace string {
        /**
         * modifies `str` and replace strings matching `from` with value from `to`
         * @param str input string
         * @param from string to find
         * @param to replacement string
         */
        inline void replace(std::string &str, const std::string &from, const std::string &to) {
            auto pos = str.find(from);
            while (pos != std::string::npos) {
                str.replace(pos, std::size(from), to);
                pos = str.find(from);
            }
        }

        /**
         * replace strings matching `from` with value from `to` and returns a new string
         *
         * Note: this method requires in-place initialization std::string{...} or std::move(...)
         * @param str input string
         * @param from string to find
         * @param to replacement string
         * @return a new string containing the replaced values
         */
        inline std::string replace(std::string &&str, const std::string &from, const std::string &to) {
            replace(str, from, to);
            return str;
        }

        /**
         * searches a val on the provided str
         * @param str string to search on
         * @param val value to search on str
         * @return true if str contains val
         */
        inline bool contains(std::string &str, std::string &val) {
            return str.find(val) != std::string::npos;
        }

        /**
         * checks if str ends with prefix
         * @param str string to search on
         * @param postfix postfix to search on str
         * @return true if str ends with postfix
         */
        inline bool endsWith(const std::string &str, const std::string &postfix) {
            if (std::size(str) < std::size(postfix))
                return false;

            return str.compare(str.length() - postfix.length(), postfix.length(), postfix) == 0;
        }

        /**
         * checks if str starts with prefix
         * @param str string to search on
         * @param prefix prefix to search on str
         * @return true if str starts with prefix
         */
        inline bool startsWith(const std::string &str, const std::string &prefix) {
            if (std::size(str) < std::size(prefix))
                return false;

            return str.rfind(prefix) == 0;
        }

        /**
         * splits a string into a vector of strings using the delimiter provided
         *
         * Note: empty delimiter at the end of string is discarded
         * @param str string to split
         * @param delimiter split delimiter
         * @return a vector containing the split string
         */
        template<typename T, typename U, std::enable_if_t<
            std::is_assignable_v<std::string, T> &&
            std::is_assignable_v<std::string, U>
            , int> = 0>
        std::vector<std::string> split(const T &str, const U &delimiter) {
            const std::string lstr{str};

            // early return when delim is empty
            const std::string ldelim{delimiter};
            size_t delimLength = std::size(ldelim);
            if (delimLength == 0)
                return std::vector{lstr};

            // early return when str is empty
            size_t strLength = std::size(lstr);
            if (strLength == 0)
                return std::vector{lstr};

            // early return when delim is too big for string
            if (delimLength > strLength)
                return std::vector{lstr};

            std::vector<std::string> result{};
            size_t tail = 0;
            size_t head{};

            // finds the next instance of the delimiter and adds the
            // string segment to the result vector.
            // this loop continues until the tail reaches the size of the str
            // or find returns std::string::npos
            do {
                head = lstr.find(ldelim, tail);
                result.emplace_back(lstr.substr(tail, head - tail));
                tail = head + delimLength;
            } while (head != std::string::npos);

            return result;
        }
    }
}
