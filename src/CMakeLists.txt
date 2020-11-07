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

add_library(fuzzy INTERFACE)
target_include_directories(fuzzy INTERFACE "${PROJECT_SOURCE_DIR}/src/fuzzy")

add_library(unary_function INTERFACE)
target_include_directories(unary_function INTERFACE "${PROJECT_SOURCE_DIR}/src/function")

add_library(operations INTERFACE)
target_include_directories(operations INTERFACE "${PROJECT_SOURCE_DIR}/src/operation")

add_library(control INTERFACE)
target_include_directories(control INTERFACE "${PROJECT_SOURCE_DIR}/src/control")

add_executable(zad1 main.cpp control/operand.cpp)
target_link_libraries(zad1 PUBLIC domain)
target_link_libraries(zad1 INTERFACE fuzzy_set unary_function control)
