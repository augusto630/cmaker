#include "cmaker.h"

#include <filesystem>
#include <fstream>

// #include "embedded_package.h"
#include "release_assert.h"
#include "../gen/Debug/embedded_package.h"
//
// #define write(folder, file, ext) \
//     assert(std::filesystem::exists(#file "." #ext) == false, "Directory is not empty, " file "." ext "already exists."); \
//     std::ofstream file {#file "." #ext, std::ios::out | std::ios::trunc}; \
//     assert( file .is_open(), strerror(errno)); \
//     file << embedded:: ##folder##_##file##_##ext## _sv << std::endl; \
//     file .close()


#define PROJECT_NAME "#PROJECT_NAME"

namespace cmaker {

    std::string main::replaceProjectName(const std::string &projectName, std::string_view content) {
        std::string result{content};

        auto pos = result.find(PROJECT_NAME);
        while (pos != std::string::npos) {
            result.replace(pos, std::size(PROJECT_NAME) - 1, projectName);
            pos = result.find(PROJECT_NAME);
        }

        return result;
    }

    void main::write(const std::string &projectName, const std::string &dir, const std::string &file,
                     const std::string_view content) {
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

        fileStream << replaceProjectName(projectName, content) << std::endl;
        fileStream.close();
        assert(fileStream.good(), "failed saving file " << path << strerror(errno));

        print("Created file ", path, "\n");
    }

    int main::run() const {
        const auto path = std::filesystem::current_path();

        print("CMaker v1.0.0\n");
        print("Using args:\n");
        print("   Project Name: ", args.projectName, "\n");
        print("   Truncate: ", std::boolalpha, args.truncate, std::noboolalpha, "\n");
        print("   Dry-run: ", std::boolalpha, args.dryRun, std::noboolalpha, "\n");

        for (const auto &[identifier, content]: embedded::files) {
            assert(!identifier.empty(), "empty identifier")

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

            file = replaceProjectName(args.projectName, file);
            write(args.projectName, dir, file, content);
        }

        return EXIT_SUCCESS;
    }
} // cmaker
