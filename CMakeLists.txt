cmake_minimum_required(VERSION 4.0)

project(guess_the_number)

set(CMAKE_CXX_STANDARD 17)

add_executable(guess_the_number
        main.cpp
        game.cpp
        game.h
        high_scores.h
        high_scores.cpp)