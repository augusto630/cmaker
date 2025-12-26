# CMake-r
Pronounced `See-make-lower-case-r`

Initializes a cmake project using the following settings:
- `Clang/Clang++`
- `C++ 17`
- Conformant C++ Enabled
- Binaries output to ./out/
- Configured `Google Test`
- Configured `Include what you use - iwyu`
- Release assertions

## Dependencies
- `Clang` <- must be installed manually
- `iwyu` <- must be installed manually
- `Google Test` <- automatically fetched

## Structure
```
├─CMakeLists.txt
├─main.cpp
├─.gitignore
├─src
│ ├───CMakeLists.txt
│ ├───[project name].cpp
│ ├───[project name].h
│ └───release_assert.h
├─test
│ ├───CMakeLists.txt
│ └───[project name].cpp
└─out
  ├───Debug
  │   └───[project name]
  └───Release
      └───[project name]
```

The source code and structure provided, enables quickly setting up a working cross-platform C++ project without having 
to customize trivial settings, such as which compiler to use, version of C++, how to configure tests, and how a basic code
architecture should look like

A simple abstraction is provided for decoupling the main function from the application code.
This is achieved by redirecting calls from the `main(...)` function to an object called `[project name]` where arguments
can be parsed, as well as the initial logic for the application to be inserted.

A simple header only file is also provided to facilitate release time asserts, see `release_assert.h` for more details.

## Usage
```bash
Usage: cmaker [Options] [Arg]

Options: [-h|--help] print this help
         [-t|--truncate] truncates existing files
         [-d|--dry] executes a dry-run
         [-p|--project] [Arg] specifies the project name, if omitted, the current directory will be used instead.

Example:
    cmaker -d
    cmaker -p MyProject
```

