#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>

#include "args.h"

namespace cmaker {
    class main {
        argsInfo args;

        template<typename... T>
        void print(T &... t) const;

    public:
        static std::string replaceProjectName(const std::string &projectName, std::string_view content);

        void write(const std::string &projectName, const std::string &dir, const std::string &file,
                   std::string_view content) const;

        [[nodiscard]] int run(int argc, const char *const*argv);
    };
}
