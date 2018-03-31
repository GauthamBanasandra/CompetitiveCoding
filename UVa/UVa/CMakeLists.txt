cmake_minimum_required(VERSION 3.8)
project(UVa)

set(CMAKE_CXX_STANDARD 11)

# Complete search
    # Iterative
        # Linear scan
        add_executable(Integer_sequence_from "Complete search/Iterative/Linear scan/Integer sequence from/Integer sequence from.cpp")
        add_executable(Expert_enough "Complete search/Iterative/Linear scan/Expert enough/Expert enough.cpp")
        add_executable(Fractions_again "Complete search/Iterative/Linear scan/Fractions again/Fractions again.cpp")
        # Two nested loops
        add_executable(Sales "Complete search/Iterative/Two nested loops/Sales/Sales.cpp")
        add_executable(Closest_sums "Complete search/Iterative/Two nested loops/Closest sums/Closest sums.cpp")
        add_executable(Tour_de_france "Complete search/Iterative/Two nested loops/Tour de france/Tour de france.cpp" "Complete search/Iterative/Two nested loops/Tour de france/utils.cpp")
        # Three or more nested loops
        add_executable(Lotto "Complete search/Iterative/Three or more nested loops/Easy/Lotto/Lotto.cpp" "Complete search/Iterative/Three or more nested loops/Easy/Lotto/utils.cpp")
        add_executable(Dart_a_mania "Complete search/Iterative/Three or more nested loops/Easy/Dart-a-mania/Dart-a-mania.cpp" "Complete search/Iterative/Three or more nested loops/Easy/Dart-a-mania/utils.cpp")
        add_executable(The_path_in_the_colored_field "Complete search/Iterative/Three or more nested loops/Easy/The path in the colored field/The path in the colored field.cpp" "Complete search/Iterative/Three or more nested loops/Easy/The path in the colored field/utils.cpp")
        add_executable(Simple_equations "Complete search/Iterative/Three or more nested loops/Hard/Simple equations/Simple equations.cpp")
        # Fancy techniques
        add_executable(Bars "Complete search/Iterative/Fancy techniques/Bars/Bars.cpp")
        add_executable(Zones "Complete search/Iterative/Fancy techniques/Zones/Zones.cpp")
        add_executable(Grid_game "Complete search/Iterative/Fancy techniques/Grid game/Grid game.cpp" "Complete search/Iterative/Fancy techniques/Grid game/util.cpp")
    # Recursive backtracking
        # Easy
        add_executable(The_sultans_successor "Complete search/Recursive backtracking/Easy/The sultans successor/The sultans successor.cpp" "Complete search/Recursive backtracking/Easy/The sultans successor/utils.cpp")
        add_executable(Call_forwarding "Complete search/Recursive backtracking/Easy/Call forwarding/Call forwarding.cpp" "Complete search/Recursive backtracking/Easy/Call forwarding/utils.cpp")
        add_executable(The_settlers_of_catan "Complete search/Recursive backtracking/Easy/The settlers of catan/The settlers of catan.cpp" "Complete search/Recursive backtracking/Easy/The settlers of catan/utils.cpp")
        add_executable(CD "Complete search/Recursive backtracking/Easy/CD/CD.cpp")
        add_executable(Passwords "Complete search/Recursive backtracking/Easy/Passwords/Passwords.cpp")
        add_executable(All_walks_of_length_n_from_first_node "Complete search/Recursive backtracking/Easy/All walks of length n from first node/All walks of length n from first node.cpp" "Complete search/Recursive backtracking/Easy/All walks of length n from first node/utils.cpp")
        add_executable(The_hamming_distance_problem "Complete search/Recursive backtracking/Easy/The hamming distance problem/The hamming distance problem.cpp")
        add_executable(8_queens_chess_problem "Complete search/Recursive backtracking/Easy/8 queens chess problem/8 queens chess problem.cpp")
        add_executable(Hanoi_tower_troubles_again "Complete search/Recursive backtracking/Easy/Hanoi tower troubles again/Hanoi tower troubles again.cpp")
        add_executable(23_out_of_5 "Complete search/Recursive backtracking/Easy/23 out of 5/23 out of 5.cpp")
        add_executable(Marcus_help "Complete search/Recursive backtracking/Easy/Marcus help/Marcus help.cpp")
        add_executable(Back_to_the_8_queens "Complete search/Recursive backtracking/Easy/Back to the 8 queens/Back to the 8 queens.cpp")
# Adhoc
    # Anagram
    add_executable(Anagram "Ad hoc/Anagram/Anagram/Anagram.cpp")
    add_executable(Anagrams "Ad hoc/Anagram/Anagrams/Anagrams.cpp")
    add_executable(Ananagrams "Ad hoc/Anagram/Ananagrams/Ananagrams.cpp")
    # Card
    add_executable(Bridge_hand_evaluator "Ad hoc/Card/Bridge hand evaluator/Bridge hand evaluator.cpp")
    add_executable(What_is_the_card "Ad hoc/Card/What is the card/What is the card.cpp")
    add_executable(Jollo "Ad hoc/Card/Jollo/Jollo.cpp")
    # Chess
    add_executable(Chess "Ad hoc/Chess/Chess/Chess.cpp")
    add_executable(Chessboard_in_fen "Ad hoc/Chess/Chessboard in FEN/Chessboard in FEN.cpp")
    add_executable(How_many_knights "Ad hoc/Chess/How many knights/How many knights.cpp")
    # Others
    add_executable(Bowling "Ad hoc/Others/Bowling/Bowling.cpp")
    add_executable(Hangman_judge "Ad hoc/Others/Hangman judge/Hangman judge.cpp")
    add_executable(Minesweeper "Ad hoc/Others/Minesweeper/Minesweeper.cpp")
    add_executable(Snakes_and_ladders "Ad hoc/Others/Snakes and ladders/Snakes and ladders.cpp")
    add_executable(Traditional_BINGO "Ad hoc/Others/Traditional BINGO/Traditional BINGO.cpp")
    # Palindrome
    add_executable(Magic_square_palindromes "Ad hoc/Palindrome/Magic square palindromes/Magic square palindromes.cpp")
    add_executable(Mother_bear "Ad hoc/Palindrome/Mother bear/Mother bear.cpp")
    add_executable(Palindromes "Ad hoc/Palindrome/Palindromes/Palindromes.cpp")