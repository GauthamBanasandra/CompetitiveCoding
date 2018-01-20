cmake_minimum_required(VERSION 3.9)
project(UVa)

set(CMAKE_CXX_STANDARD 11)

add_executable(Integer_sequence_from "Complete search/Iterative/Linear scan/Integer sequence from/Integer sequence from.cpp")
add_executable(Expert_enough "Complete search/Iterative/Linear scan/Expert enough/Expert enough.cpp")
add_executable(Fractions_again "Complete search/Iterative/Linear scan/Fractions again/Fractions again.cpp")
add_executable(Sales "Complete search/Iterative/Two nested loops/Sales/Sales.cpp")
add_executable(Closest_sums "Complete search/Iterative/Two nested loops/Closest sums/Closest sums.cpp")
add_executable(Tour_de_france "Complete search/Iterative/Two nested loops/Tour de france/Tour de france.cpp" "Complete search/Iterative/Two nested loops/Tour de france/utils.cpp")
add_executable(Lotto "Complete search/Iterative/Three or more nested loops/Easy/Lotto/Lotto.cpp" "Complete search/Iterative/Three or more nested loops/Easy/Lotto/utils.cpp")
add_executable(Dart_a_mania "Complete search/Iterative/Three or more nested loops/Easy/Dart-a-mania/Dart-a-mania.cpp" "Complete search/Iterative/Three or more nested loops/Easy/Dart-a-mania/utils.cpp")

add_executable(Anagram "Ad hoc/Anagram/Anagram/Anagram.cpp")
add_executable(Anagrams "Ad hoc/Anagram/Anagrams/Anagrams.cpp")
add_executable(Ananagrams "Ad hoc/Anagram/Ananagrams/Ananagrams.cpp")
add_executable(Bridge_hand_evaluator "Ad hoc/Card/Bridge hand evaluator/Bridge hand evaluator.cpp")
add_executable(What_is_the_card "Ad hoc/Card/What is the card/What is the card.cpp")

