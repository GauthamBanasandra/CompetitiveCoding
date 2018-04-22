cmake_minimum_required(VERSION 3.8)
project(Hackerrank)

set(CMAKE_CXX_STANDARD 11)

add_executable(Strong_password "Strong password/Strong password.cpp")
add_executable(The_salesman "The salesman/The salesman.cpp")
add_executable(Marcs_cakewalk "Marcs cakewalk/Marcs cakewalk.cpp")
add_executable(The_power_sum "The power sum/The power sum.cpp" "The power sum/utils.cpp")

# Week of code 37
    add_executable(The_average_of_top_employees "Week of code 37/The average of top employees/The average of top employees.cpp")
    add_executable(Simple_language "Week of code 37/Simple language/Simple language.cpp")
    add_executable(Dynamic_line_intersection "Week of code 37/Dynamic line intersection/Dynamic line intersection.cpp")