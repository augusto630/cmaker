if (ENABLE_IWYU)
    # Configure iwyu
    # iwyu will warn when missing a required include
    find_program(iwyu_path NAMES include-what-you-use iwyu REQUIRED)

    # Exclude cmake-build folders
    set(iwyu_common_args ${iwyu_path} -Xiwyu;--exclude=.*cmake-build-.*)
    set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_common_args})
    set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY C_INCLUDE_WHAT_YOU_USE ${iwyu_common_args})

    find_package(Python3 REQUIRED COMPONENTS Interpreter)

    # Fix includes automatically
    # Requires iwyu_tool.py and fix_includes.py to be present on path
    add_custom_target(fix_includes_iwyu
            COMMAND iwyu_tool.py --exclude=cmake-build-debug --exclude=cmake-build-release -p ${CMAKE_BINARY_DIR} > ${CMAKE_BINARY_DIR}/iwyu.out
            COMMAND fix_includes.py < ${CMAKE_BINARY_DIR}/iwyu.out
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            USES_TERMINAL
    )
endif ()