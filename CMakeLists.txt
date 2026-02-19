cmake_minimum_required(VERSION 4.0)

project(guess_the_number)

set(CMAKE_CXX_STANDARD 17)

add_executable(guess_the_number
        main.cpp
        game.cpp
        high_scores.cpp
        argument.cpp)