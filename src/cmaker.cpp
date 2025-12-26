#include "cmaker.h"

#include <_stdlib.h>
#include <errno.h>
#include <_string.h>
#include <string>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <utility>
#include <iostream>
#include <unordered_map>

#include "release_assert.h"
#include "embedded_package.h"
#include "version.h"
#include "strings_helper.h"

#define PROJECT_NAME "#PROJECT_NAME"

namespace cmaker {
    template<typename... T>
    void main::print(T &... t) const {
        if (args.quiet)
            return;

        // ((expr)...) fold expansion, it recursively calls expr as long as there are ... to unpack
        ((std::cout << t), ...);
    }

    void main::write(const std::string &projectName, const std::string &dir, const std::string &file,
                     const std::string_view content) const {
        std::filesystem::path path = std::filesystem::current_path();
        path /= dir;
        path /= file;

        if (args.dryRun) {
            print("Would create file ", path, "\n");
            return;
        }

        assert(args.truncate || std::filesystem::exists(path) == false, "file " << path << " already exists.");

        // Create parent directory if it doesn't exist
        if (std::filesystem::exists(path.parent_path()) == false) {
            assert(std::filesystem::create_directories(path.parent_path()), "failed creating dir for " << path)
        }

        std::ofstream fileStream{path, std::ios::out | std::ios::trunc};
        assert(fileStream.is_open(), strerror(errno));

        fileStream << strings::replace(std::string{content}, PROJECT_NAME, projectName);
        fileStream.close();
        assert(fileStream.good(), "failed saving file " << path << strerror(errno));

        print("Created file ", path, "\n");
    }

    int main::run(const int argc, const char *const*argv) {
        if (args.parseArgs(argc, argv) == false) {
            return EXIT_FAILURE;
        };

        const auto path = std::filesystem::current_path();

        print("CMaker v", version::semantic, "\n");
        print("Using args:\n");
        print("   Project Name: ", args.projectName, "\n");
        print("   Truncate: ", std::boolalpha, args.truncate, std::noboolalpha, "\n");
        print("   Dry-run: ", std::boolalpha, args.dryRun, std::noboolalpha, "\n");

        for (const auto &[identifier, content]: embedded::files) {
            assert(!identifier.empty(), "empty identifier")

            // Skipped files starts with _
            if (identifier[0] == '_')
                continue;

            std::string dir{};
            std::string file{};
            auto divPos = identifier.find('_');
            if (divPos != std::string::npos) {
                dir = identifier.substr(0, divPos);

                assert(divPos < identifier.size(), "identifier does not contain file name");
                file = identifier.substr(divPos + 1);
            } else {
                file = identifier;
            }

            file = strings::replace(std::string{file}, PROJECT_NAME, args.projectName);
            write(args.projectName, dir, file, content);
        }

        return EXIT_SUCCESS;
    }
} // cmaker
