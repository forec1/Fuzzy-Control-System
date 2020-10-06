# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

set(This ZAD1)

# Name of the project and version
project(${This}
    VERSION 1.0
    LANGUAGES C CXX
)

# Specify C and  C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)

# Generate compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()
option(BUILD_TESTING "Build the tests" ON)

add_subdirectory(src)
add_subdirectory(lib)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
