cmake_minimum_required(VERSION 4.0)

project(ContainersTests)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(containers_tests
        tests/vector_tests.cpp
        tests/list_tests.cpp)

target_link_libraries(containers_tests gtest_main gtest)