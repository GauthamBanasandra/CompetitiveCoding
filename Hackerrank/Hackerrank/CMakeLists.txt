cmake_minimum_required(VERSION 3.8)
project(Hackerrank)

set(CMAKE_CXX_STANDARD 11)

find_package(Java REQUIRED)
include(UseJava)

# Practice
    # Strings
    add_executable(Strong_password "Practice/Strings/Strong password/Strong password.cpp")
    # Graph theory
    add_executable(The_salesman "Practice/Graph_theory/The salesman/The salesman.cpp")
    add_executable(Marcs_cakewalk "Practice/Greedy/Marcs cakewalk/Marcs cakewalk.cpp")
    # Recursion
    add_executable(Recursive_digit_sum "Practice/Recursion/Recursive digit sum/Recursive digit sum.cpp")
    add_executable(The_power_sum "Practice/Recursion/The power sum/The power sum.cpp"
            "Practice/Recursion/The power sum/utils.cpp")
    # Greedy
    add_executable(Beautiful_pairs "Practice/Greedy/16828/Beautiful pairs.cpp")

# Compete
    # Week of code
        # 37
        add_executable(The_average_of_top_employees "Compete/Week of code/37/The average of top employees/The average of top employees.cpp")
        add_executable(Simple_language "Compete/Week of code/37/Simple language/Simple language.cpp")
        add_executable(Dynamic_line_intersection "Compete/Week of code/37/Dynamic line intersection/Dynamic line intersection.cpp")
    # Hourrank
    add_executable(Video_conference "Compete/Hourrank/30/Video conference/Video conference.cpp")
    # Goldman Sachs CodeSprint
    add_executable(Bank_accounts "Compete/Goldman Sachs CodeSprint/Goldman Sachs CodeSprint/main.cpp"
            "Compete/Goldman Sachs CodeSprint/Goldman Sachs CodeSprint/Bank accounts.cpp")
    # NSE ISB CodeSprint
    add_executable(Cross_over "Compete/NSE ISB CodeSprint/NSE ISB CodeSprint/CrossOver.cpp")
    # Stryker CodeSprint
    add_jar(Minimum_index_difference "Compete/StrykerCodeSprint/Minimum index difference/src/MinimumIndexDifference.java")
    add_jar(Point_filtering "Compete/StrykerCodeSprint/Point filtering/src/PointFiltering.java")