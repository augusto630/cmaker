#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <string_view>

#include "args.h"

namespace cmaker {
    class main {
        argsInfo args{};

        template<typename... T>
        void print(T &... t) const;

    public:
        void write(const std::string &projectName, const std::string &dir, const std::string &file,
                   std::string_view content) const;

        [[nodiscard]] int run(int argc, const char *const*argv);
    };
}
