cmake_minimum_required(VERSION 4.1)

# Make sure that clang setting is done after gtest
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE})

project(#PROJECT_NAME)

add_subdirectory(src)
add_subdirectory(test)

# Configure project
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_PROJECT_NAME}_lib)

option(ENABLE_IWYU "Enable include-what-you-use" ON)
include(iwyu.cmake)



