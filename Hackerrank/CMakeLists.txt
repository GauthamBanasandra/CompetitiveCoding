cmake_minimum_required(VERSION 3.8)
project(Hackerrank)

set(CMAKE_CXX_STANDARD 17)

find_package(Java REQUIRED)
include(UseJava)

# Practice
    # Strings
    add_executable(Strong_password "Practice/Strings/Strong password/Strong password.cpp")
    # Graph theory
    add_executable(The_salesman "Practice/Graph_theory/The salesman/The salesman.cpp")
    add_executable(Roads_and_libraries "Practice/Graph_theory/Roads and libraries/Roads and libraries.cpp")
    add_executable(Journey_to_the_moon "Practice/Graph_theory/Journey to the moon/Journey to the moon.cpp")
    add_executable(BFS_shortest_reach "Practice/Graph_theory/BFS shortest reach/BFS shortest reach.cpp")
    add_executable(Kruskal_mst_really_special_subtree "Practice/Graph_theory/Kruskal MST really special subtree/Kruskal MST really speciak subtree.cpp")
    add_executable(Snakes_and_ladders_the_quickest_way_up "Practice/Graph_theory/Snakes and ladders the quickest way up/Snakes and ladders the quickest way up.cpp")
    # Recursion
    add_executable(Recursive_digit_sum "Practice/Recursion/Recursive digit sum/Recursive digit sum.cpp")
    add_executable(The_power_sum "Practice/Recursion/The power sum/The power sum.cpp"
            "Practice/Recursion/The power sum/utils.cpp")
    # Greedy
    add_executable(Beautiful_pairs "Practice/Greedy/16828/Beautiful pairs.cpp")
    add_executable(Marcs_cakewalk "Practice/Greedy/Marcs cakewalk/Marcs cakewalk.cpp")
    # Dyanmic programming
    add_executable(Hackerrank_Coin_change "Practice/Dynamic_programming/Coin change/Coin change.cpp")
    add_executable(The_coin_change_problem "Practice/Dynamic_programming/The coin change problem/The coin change problem.cpp")
    add_executable(Sherlock_and_cost "Practice/Dynamic_programming/Sherlock and cost/Sherlock and cost.cpp")
    add_executable(Sam_and_substrings "Practice/Dynamic_programming/Sam and substrings/Sam and substrings.cpp")
    # Dictionaries and hashmaps
    add_jar(Frequency_queries "Practice/Dictionaries and hashmaps/Frequency queries/src/main/java/Solution.java")

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