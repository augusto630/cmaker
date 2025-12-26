# Create shared lib
add_library(${CMAKE_PROJECT_NAME}_lib SHARED
        ${CMAKE_PROJECT_NAME}.cpp
        ${CMAKE_PROJECT_NAME}.h
        release_assert.h
)

target_include_directories(${CMAKE_PROJECT_NAME}_lib INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/../gen/${CMAKE_BINARY_DIR}
)
