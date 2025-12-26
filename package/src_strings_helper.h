#pragma once
#include <string>

namespace #PROJECT_NAME::strings {
    /**
     * modifies `str` and replace strings matching `from` with value from `to`
     * @param str input string
     * @param from string to find
     * @param to replacement string
     */
    inline void replace(std::string& str, const std::string& from, const std::string& to) {
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
    inline std::string replace(std::string&& str, const std::string& from, const std::string& to) {
        replace(str, from, to);
        return str;
    }

}
