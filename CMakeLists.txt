cmake_minimum_required(VERSION 4.0)
project(TopKWords)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
endif ()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG  "-g -O0 -Wall")

add_executable(topk_words topk_words.cpp)

find_package(Threads REQUIRED)
target_link_libraries(topk_words Threads::Threads)