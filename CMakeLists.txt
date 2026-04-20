cmake_minimum_required(VERSION 4.0)

project(ContainersTests)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(containers_tests
        tests/vector_tests.cpp
        tests/list_tests.cpp)

target_link_libraries(containers_tests PRIVATE GTest::gtest_main)