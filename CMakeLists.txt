# Minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.0)

set(This ZAD1)

# Name of the project and version
project(${This}
    VERSION 1.0
    LANGUAGES C CXX
)

# Specify C and  C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD_REQUIRED True)

# Generate compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Za omogucavanje buildanja testova odkomentirati sve dole linije
# i u folder lib staviti gtest source code

enable_testing()
option(BUILD_TESTING "Build the tests" ON)

add_subdirectory(src)

# Odkomentirati ako se koriste library
# Ja sam koristio gtest za pisanje unit testova
# Samo taj kod je potrebno staviti u folder lib
add_subdirectory(lib)

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
