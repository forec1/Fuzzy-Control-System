cmake_minimum_required(VERSION 3.0)

add_executable(domain_test DomainTest.cpp)
target_link_libraries(domain_test PUBLIC
    gtest_main
    domain
)
add_test(
    NAME domain_test
    COMMAND domain_test
)

add_executable(fuzzy_set_test fuzzy_set_test.cpp)
target_link_libraries(fuzzy_set_test PUBLIC
    gtest_main
    domain
    fuzzy
    unary_function
)
add_test(
    NAME fuzzy_set_test
    COMMAND fuzzy_set_test
)

add_executable(operations_test operations_test.cpp)
target_link_libraries(operations_test PUBLIC
    gtest_main
    operations
    domain
    fuzzy
    unary_function
)
add_test(
    NAME operations_test
    COMMAND operations_test
)

add_executable(relation_test relation_test.cpp)
target_link_libraries(relation_test PUBLIC
    gtest_main
    fuzzy
    domain
)
add_test(
    NAME relation_test
    COMMAND relation_test
)
