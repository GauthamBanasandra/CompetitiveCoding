cmake_minimum_required(VERSION 3.12)
project(Leetcode)

set(CMAKE_CXX_STANDARD 14)

# Practice
    # Easy
    add_executable(Two_sum "Practice/Easy/1/Two sum.cpp")
    add_executable(Reverse_integer "Practice/Easy/7/Reverse integer.cpp")
    add_executable(Valid_parenthesis "Practice/Easy/20/Valid parenthesis.cpp")
    add_executable(Remove_duplicates_from_sorted_array "Practice/Easy/26/Remove duplicates from sorted array.cpp")
    add_executable(Maximum_subarray "Practice/Easy/53/Maximum subarray.cpp")
    # Medium
    add_executable(maximum_binary_tree "Practice/Medium/654/Maximum binary tree.cpp")
    add_executable(add_two_numbers "Practice/Medium/2/Add two numbers.cpp")
    add_executable(longest_substring_without_repeating_characters "Practice/Medium/3/Longest substring without repeating characters.cpp")
    add_executable(longest_palindromic_substring "Practice/Medium/5/Longest palindromic substring.cpp")
    add_executable(zigzag_conversion "Practice/Medium/6/Zigzag conversion.cpp")
    add_executable(string_to_integer "Practice/Medium/8/String to integer.cpp")
    add_executable(integer_to_roman "Practice/Medium/12/Integer to roman.cpp")
    add_executable(3sum "Practice/Medium/15/3Sum.cpp")
    add_executable(3sum_closest "Practice/Medium/16/3sum closest.cpp")
    add_executable(letter_combinations_of_a_phone_number "Practice/Medium/17/Letter combinations of a phone number.cpp")
    add_executable(remove_nth_node_from_end_of_list "Practice/Medium/19/Remove nth node from end of list.cpp")
    add_executable(generate_parenthesis "Practice/Medium/22/Generate parenthesis.cpp")
    add_executable(swap_nodes_in_pairs "Practice/Medium/24/Swap nodes in pairs.cpp")
    add_executable(next_permutation "Practice/Medium/31/Next permutation.cpp")
    add_executable(search_in_rotated_sorted_array "Practice/Medium/33/Search in rotated sorted array.cpp")
    add_executable(find_first_and_last_position_of_element_in_sorted_array "Practice/Medium/34/Find first and last position of element in sorted array.cpp")
    add_executable(valid_sudoku "Practice/Medium/36/Valid sudoku.cpp")
    add_executable(Combination_sum "Practice/Medium/39/Combination sum.cpp")
    add_executable(Permutations "Practice/Medium/46/Permutations.cpp")
    add_executable(Group_anagrams "Practice/Medium/49/Group anagrams.cpp")
    add_executable(Container_with_most_water "Practice/Medium/11/Container with most water.cpp")
    add_executable(Jump_game "Practice/Medium/55/Jump game.cpp")
    add_executable(Merge_intervals "Practice/Medium/56/Merge intervals.cpp")
    # Hard
    add_executable(Merge_k_sorted_lists "Practice/Hard/23/Merge k sorted lists.cpp")
    add_executable(First_missing_positive "Practice/Hard/41/First missing positive.cpp")
    add_executable(Trapping_rain_water "Practice/Hard/42/Trapping rain water.cpp")

# Compete
    # Weekly contest 135
    add_executable(Valid_boomerang "Compete/Weekly contest/135/5051/Valid boomerang.cpp")
    add_executable(Binary_search_tree_to_greater_sum_tree "Compete/Weekly contest/135/5050/Binary search tree to greater sum tree.cpp")
    # Weekly contest 136
    add_executable(Flower_planting_with_no_adjacent "Compete/Weekly contest/136/1042/Flower planting with no adjacent.cpp")