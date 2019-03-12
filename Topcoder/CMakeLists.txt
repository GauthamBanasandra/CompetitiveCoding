cmake_minimum_required(VERSION 3.8)
project(Topcoder)

set(CMAKE_CXX_STANDARD 17)

include_directories("Practice/Ab")

add_executable(Ab
    "Practice/Ab/Ab.cpp"
    "Practice/Ab/main.cpp")