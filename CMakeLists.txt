cmake_minimum_required(VERSION 4.1)

option(ENABLE_IWYU "Enable include-what-you-use" ON)
option(ENABLE_VERSION "Enable semantic-versioning" ON)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# required by iwyu
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

project(cmaker VERSION 1.0.0.0)

add_subdirectory(src)
add_subdirectory(test)

# Configure project
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

include(cmake/iwyu.cmake)
include(cmake/version.cmake)
include(cmake/embedded_package.cmake)