cmake_minimum_required(VERSION 3.0)

set(Headers
    domain/domain.hpp
    domain/domain_element.hpp
)

set(Sources
    domain/domain.cpp
    domain/domain_element.cpp
)

add_library(domain ${Sources} ${Headers})
add_executable(zad1 test.cpp)
target_link_libraries(zad1 PUBLIC domain)
