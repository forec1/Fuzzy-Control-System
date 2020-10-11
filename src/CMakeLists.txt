cmake_minimum_required(VERSION 3.0)

set(DomainHeaders
    domain/domain.hpp
    domain/domain_element.hpp
)

set(DomainSources
    domain/domain.cpp
    domain/domain_element.cpp
)

add_library(domain ${DomainSources} ${DomainHeaders})

add_library(fuzzy_set INTERFACE)
target_include_directories(fuzzy_set INTERFACE "${PROJECT_SOURCE_DIR}/src/fuzzy_set")

add_library(unitary_function INTERFACE)
target_include_directories(unitary_function INTERFACE "${PROJECT_SOURCE_DIR}/src/unitary_function")

add_library(operations INTERFACE)
target_include_directories(operations INTERFACE "${PROJECT_SOURCE_DIR}/src/operation")

add_executable(zad1 test.cpp)
target_link_libraries(zad1 PUBLIC domain)
target_link_libraries(zad1 INTERFACE fuzzy_set unitary_function)
