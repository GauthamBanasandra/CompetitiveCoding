cmake_minimum_required(VERSION 3.10)
project(Hacker_cup)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tourist "Qualification round/Tourist/Tourist.cpp" utils/print.cpp)
add_executable(Let_it_flow "Round 1/Let it flow/Let it flow.cpp")