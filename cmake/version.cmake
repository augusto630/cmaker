if (ENABLE_VERSION)
    # Make sure to output to a separate folder on each build
    # Builds run concurrently and override each other changes
    set(VERSION_HEADER ${CMAKE_BINARY_DIR}/gen/version.h)

    # Write include and namespace
    file(WRITE ${VERSION_HEADER} "// auto-generated\n")
    file(APPEND ${VERSION_HEADER} "#pragma once\n\n")
    file(APPEND ${VERSION_HEADER} "namespace ${CMAKE_PROJECT_NAME}::version {\n")
    file(APPEND ${VERSION_HEADER} "inline constexpr auto major{${CMAKE_PROJECT_VERSION_MAJOR}};\n")
    file(APPEND ${VERSION_HEADER} "inline constexpr auto minor{${CMAKE_PROJECT_VERSION_MINOR}};\n")
    file(APPEND ${VERSION_HEADER} "inline constexpr auto patch{${CMAKE_PROJECT_VERSION_PATCH}};\n")
    file(APPEND ${VERSION_HEADER} "inline constexpr auto build{${CMAKE_PROJECT_VERSION_TWEAK}};\n")
    file(APPEND ${VERSION_HEADER} "inline constexpr auto semantic{\"${CMAKE_PROJECT_VERSION}\"};\n")
    file(APPEND ${VERSION_HEADER} "}\n")
endif ()