if(DEFINED EMBEDDED_PACKAGE_ALREADY_GENERATED)
    return()
endif()

set(EMBEDDED_PACKAGE_ALREADY_GENERATED TRUE)

set(PACKAGE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB PACKAGE_FILES "${PACKAGE_DIR}/files/*")
list(SORT PACKAGE_FILES)

# Make sure to output to a separate folder on each build
# Builds run concurrently and override each other changes
set(OUT_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/../gen/${CMAKE_BUILD_TYPE}/embedded_package.h)

# Write include and namespace
file(WRITE ${OUT_HEADER} "// auto-generated\n#pragma once\n\n")
file(APPEND ${OUT_HEADER} "#include <string_view>\n#include <unordered_map>\n\n")
file(APPEND ${OUT_HEADER} "namespace embedded {\n\n")

# Write file content
foreach (FILE ${PACKAGE_FILES})
    get_filename_component(NAME ${FILE} NAME)
    string(REPLACE "." "_" VAR ${NAME})
    string(REPLACE "#" "_" VAR ${VAR})

    file(READ ${FILE} CONTENT)
#    string(REPLACE "\\" "\\\\" CONTENT "${CONTENT}")
#    string(REPLACE "\"" "\\\"" CONTENT "${CONTENT}")

    file(APPEND ${OUT_HEADER}
            "inline constexpr char ${VAR}[] = R\"(${CONTENT})\";\n\n"
    )
endforeach ()

# Create string view
foreach(FILE ${PACKAGE_FILES})
    get_filename_component(NAME ${FILE} NAME)
    string(REPLACE "." "_" VAR ${NAME})
    string(REPLACE "#" "_" VAR ${VAR})

    file(APPEND ${OUT_HEADER}
            "inline constexpr std::string_view ${VAR}_sv{${VAR}};\n\n"
    )
endforeach()

# Declare files map
file(APPEND ${OUT_HEADER}
        "inline const std::unordered_map<std::string, std::string_view> files = {\n"
)

# Build files map
foreach (FILE ${PACKAGE_FILES})
    get_filename_component(NAME ${FILE} NAME)
    string(REPLACE "." "_" VAR ${NAME})
    string(REPLACE "#" "_" VAR ${VAR})

    file(APPEND ${OUT_HEADER}
            "    {\"${NAME}\", embedded::${VAR}_sv},\n"
    )
endforeach ()

file(APPEND ${OUT_HEADER}
        "};\n\n} // namespace embedded\n"
)