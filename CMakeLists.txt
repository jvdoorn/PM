cmake_minimum_required(VERSION 3.15)
project(PM)

set(CMAKE_CXX_STANDARD 14)

include_directories(assignment4)

add_executable(assignment1 assignment1/doorn1.cpp)
add_executable(assignment2 assignment2/doorn2.cpp)
add_executable(assignment3 assignment3/doorn3.cpp)
add_executable(assignment4 assignment4/main.cpp assignment4/board.cpp assignment4/board.h)

add_executable(practice practice/main.cpp)