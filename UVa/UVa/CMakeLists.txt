cmake_minimum_required(VERSION 3.8)
project(UVa)

set(CMAKE_CXX_STANDARD 11)

# Introduction
    # Super easy
    add_executable(Cost_cutting "Introduction/Super easy/11727/Cost cutting.cpp")
    add_executable(Division_of_nlogonia "Introduction/Super easy/11498/Division of nlogonia.cpp")
    add_executable(Relational_operators "Introduction/Super easy/11172/Relational operators.cpp")
    # Easy
    add_executable(Event_planning "Introduction/Easy/11559/Event planning.cpp")
    add_executable(Horror_dash "Introduction/Easy/11799/Horror dash.cpp")
    # Medium
    add_executable(Bender_B_Rodriguez "Introduction/Medium/11507/Bender B Rodriguez.cpp")
    add_executable(Request_for_proposal "Introduction/Medium/10141/Request for proposal.cpp")
    add_executable(The_snail "Introduction/Medium/573/The snail.cpp")
    # Adhoc
        # 195
        add_executable(Anagram "Introduction/Ad hoc/Anagram/195/Anagram.cpp")
        add_executable(Anagrams "Introduction/Ad hoc/Anagram/454/Anagrams.cpp")
        add_executable(Ananagrams "Introduction/Ad hoc/Anagram/156/Ananagrams.cpp")
        # Card
        add_executable(Bridge_hand_evaluator "Introduction/Ad hoc/Card/462/Bridge hand evaluator.cpp")
        add_executable(What_is_the_card "Introduction/Ad hoc/Card/10646/What is the card.cpp")
        add_executable(Jollo "Introduction/Ad hoc/Card/12247/Jollo.cpp")
        # 278
        add_executable(Chess "Introduction/Ad hoc/Chess/278/Chess.cpp")
        add_executable(Chessboard_in_fen "Introduction/Ad hoc/Chess/10284/Chessboard in FEN.cpp")
        add_executable(How_many_knights "Introduction/Ad hoc/Chess/696/How many knights.cpp")
        # Others
        add_executable(Bowling "Introduction/Ad hoc/Others/Bowling/Bowling.cpp")
        add_executable(Hangman_judge "Introduction/Ad hoc/Others/Hangman judge/Hangman judge.cpp")
        add_executable(Minesweeper "Introduction/Ad hoc/Others/Minesweeper/Minesweeper.cpp")
        add_executable(Snakes_and_ladders "Introduction/Ad hoc/Others/Snakes and ladders/Snakes and ladders.cpp")
        add_executable(Traditional_BINGO "Introduction/Ad hoc/Others/Traditional BINGO/Traditional BINGO.cpp")
        # Palindrome
        add_executable(Magic_square_palindromes "Introduction/Ad hoc/Palindrome/Magic square palindromes/Magic square palindromes.cpp")
        add_executable(Mother_bear "Introduction/Ad hoc/Palindrome/Mother bear/Mother bear.cpp")
        add_executable(Palindromes "Introduction/Ad hoc/Palindrome/Palindromes/Palindromes.cpp")
        # Real life problems
        add_executable(Beat_the_spread "Introduction/Ad hoc/Real life problems/Beat the spread/Beat the spread.cpp")
        add_executable(Boolket_printing "Introduction/Ad hoc/Real life problems/Booklet printing/Booklet printing.cpp")
        add_executable(Consanguine_calculations "Introduction/Ad hoc/Real life problems/Consanguine calculations/Consanguine calculations.cpp"
                "Introduction/Ad hoc/Real life problems/Consanguine calculations/utils.cpp")
        add_executable(Counterfeit_dollar "Introduction/Ad hoc/Real life problems/Counterfeit dollar/Counterfeit dollar.cpp")
        add_executable(Postscript "Introduction/Ad hoc/Real life problems/Postscript/Postscript.cpp"
                "Introduction/Ad hoc/Real life problems/Postscript/util.cpp")
        add_executable(Traffic_lights "Introduction/Ad hoc/Real life problems/Traffic lights/Traffic lights.cpp"
                "Introduction/Ad hoc/Real life problems/Traffic lights/utils.cpp")
        # Time
        add_executable(Clock_hands "Introduction/Ad hoc/Time/Clock hands/Clock hands.cpp")
        # Solved in Java - Clock hands
        # Solved in Java - Y3K
        # Time waster problems
        add_executable(All_integer_average "Introduction/Ad hoc/Time waster problems/All integer average/All integer average.cpp")
        add_executable(Mobile_casanova "Introduction/Ad hoc/Time waster problems/Mobile casanova/Mobile casanova.cpp")

# Data structures and libraries
    # Linear DS builtin lib
        # 1D array manipulation
        add_executable(Army_buddies "Data structures and libraries/Linear DS builtin lib/1D array manipulation/Army buddies/Army buddies.cpp")
        add_executable(Jolly_jumpers "Data structures and libraries/Linear DS builtin lib/1D array manipulation/Jolly jumpers/Jolly jumpers.cpp")
        add_executable(Newspaper "Data structures and libraries/Linear DS builtin lib/1D array manipulation/Newspaper/Newspaper.cpp")
        # 2D array manipulation
        add_executable(Grid_successor "Data structures and libraries/Linear DS builtin lib/2D array manipulation/Grid successor/Grid successor.cpp")
        add_executable(Rotated_squares "Data structures and libraries/Linear DS builtin lib/2D array manipulation/Rotated squares/Rotated squares.cpp")
        add_executable(Spiral_tap "Data structures and libraries/Linear DS builtin lib/2D array manipulation/Spiral tap/Spiral tap.cpp")
        # Bit manipulation
        add_executable(Multitasking "Data structures and libraries/Linear DS builtin lib/Bit manipulation/Multitasking/Multitasking.cpp")
        add_executable(Splitting_numbers "Data structures and libraries/Linear DS builtin lib/Bit manipulation/Splitting numbers/Splitting numbers.cpp")
        # C++ STL algorithm
        add_executable(Content_scoreboard "Data structures and libraries/Linear DS builtin lib/C++ STL algorithm/Contest scoreboard/Contest scoreboard.cpp")
        add_executable(ID_codes "Data structures and libraries/Linear DS builtin lib/C++ STL algorithm/ID codes/ID codes.cpp")
        add_executable(What_is_the_median "Data structures and libraries/Linear DS builtin lib/C++ STL algorithm/What is the median/What is the median.cpp")
        # C++ STL list
        add_executable(Broken_keyboard "Data structures and libraries/Linear DS builtin lib/C++ STL list/Broken keyboard/Broken keyboard.cpp")
        # C++ STL queue and deque
        add_executable(Frerry_loading_III "Data structures and libraries/Linear DS builtin lib/C++ STL queue and deque/Ferry loading III/Ferry loading III.cpp")
        add_executable(Ferry_loading_IV "Data structures and libraries/Linear DS builtin lib/C++ STL queue and deque/Ferry loading IV/Ferry loading IV.cpp")
        add_executable(The_lonesome_cargo_distributor "Data structures and libraries/Linear DS builtin lib/C++ STL queue and deque/The lonesome cargo distributor/The lonesome cargo distributor.cpp")
        # C++ STL stack
        add_executable(Anagrams_by_stack "Data structures and libraries/Linear DS builtin lib/C++ STL stack/Anagrams by stack/Anagrams by stack.cpp")
        add_executable(Rails "Data structures and libraries/Linear DS builtin lib/C++ STL stack/Rails/Rails.cpp")
    # Non linear DS builtin lib
        # C++ STL map
        add_executable(Conformity "Data structures and libraries/Non linear DS builtin lib/C++ STL map/Conformity/Conformity.cpp")
        add_executable(Hardwood_species "Data structures and libraries/Non linear DS builtin lib/C++ STL map/Hardwood species/Hardwood species.cpp")
        add_executable(Unique_snowflakes "Data structures and libraries/Non linear DS builtin lib/C++ STL map/Unique snowflakes/Unique snowflakes.cpp")
        # C++ STL priority_queue
        add_executable(Add_all "Data structures and libraries/Non linear DS builtin lib/C++ STL priority_queue/Add all/Add all.cpp")
        add_executable(Argus "Data structures and libraries/Non linear DS builtin lib/C++ STL priority_queue/Argus/Argus.cpp")
        add_executable(I_can_guess_the_data_structure "Data structures and libraries/Non linear DS builtin lib/C++ STL priority_queue/I can guess the data structure/I can guess the data structure.cpp")
        # C++ STL set
        add_executable(CD_stl_set "Data structures and libraries/Non linear DS builtin lib/C++ STL set/CD/CD.cpp")
        add_executable(Hoax_or_what "Data structures and libraries/Non linear DS builtin lib/C++ STL set/Hoax or what/Hoax or what.cpp")
        add_executable(Lemmings_battle "Data structures and libraries/Non linear DS builtin lib/C++ STL set/Lemmings battle/Lemmings battle.cpp")
    # DS with our own lib
        # Graph
        add_executable(Easy_problem_from_rujia_liu "Data structures and libraries/DS with our own lib/Graph/Easy problem from rujia liu/Easy problem from rujia liu.cpp")
        add_executable(Matrix_transpose "Data structures and libraries/DS with our own lib/Graph/Matrix transpose/Matrix transpose.cpp"
                "Data structures and libraries/DS with our own lib/Graph/Matrix transpose/utils.cpp")
        add_executable(The_forest_for_the_trees "Data structures and libraries/DS with our own lib/Graph/The forest for the trees/The forest for the trees.cpp")
        # Tree-related DS
        add_executable(Ahoy_pirates "Data structures and libraries/DS with our own lib/Tree-related DS/Ahoy pirates/Ahoy pirates.cpp")
        add_executable(Frequent_values "Data structures and libraries/DS with our own lib/Tree-related DS/Frequent values/Frequent values.cpp"
                "Data structures and libraries/DS with our own lib/Tree-related DS/Frequent values/utils.cpp")
        add_executable(Interval_product "Data structures and libraries/DS with our own lib/Tree-related DS/Interval product/Interval product.cpp")
        # Union-find disjoint sets
        add_executable(Network_connections "Data structures and libraries/DS with our own lib/Union-find disjoint sets/Network connections/Network connections.cpp")
        add_executable(Virtual_friends "Data structures and libraries/DS with our own lib/Union-find disjoint sets/Virtual friends/Virtual friends.cpp"
                "Data structures and libraries/DS with our own lib/Union-find disjoint sets/Virtual friends/utils.cpp")
        add_executable(Waking_up_brain "Data structures and libraries/DS with our own lib/Union-find disjoint sets/Waking up brain/Waking up brain.cpp"
                "Data structures and libraries/DS with our own lib/Union-find disjoint sets/Virtual friends/utils.cpp")

# Problem solving paradigms
    # Complete search
        # Iterative
            # Linear scan
            add_executable(Integer_sequence_from "Problem solving paradigms/Complete search/Iterative/Linear scan/Integer sequence from/Integer sequence from.cpp")
            add_executable(Expert_enough "Problem solving paradigms/Complete search/Iterative/Linear scan/Expert enough/Expert enough.cpp")
            add_executable(Fractions_again "Problem solving paradigms/Complete search/Iterative/Linear scan/Fractions again/Fractions again.cpp")
            # Two nested loops
            add_executable(Sales "Problem solving paradigms/Complete search/Iterative/Two nested loops/Sales/Sales.cpp")
            add_executable(Closest_sums "Problem solving paradigms/Complete search/Iterative/Two nested loops/Closest sums/Closest sums.cpp")
            add_executable(Tour_de_france "Problem solving paradigms/Complete search/Iterative/Two nested loops/Tour de france/Tour de france.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Two nested loops/Tour de france/utils.cpp")
            # Three or more nested loops
            add_executable(Lotto "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/Lotto/Lotto.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/Lotto/utils.cpp")
            add_executable(Dart_a_mania "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/Dart-a-mania/Dart-a-mania.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/Dart-a-mania/utils.cpp")
            add_executable(The_path_in_the_colored_field "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/The path in the colored field/The path in the colored field.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/The path in the colored field/utils.cpp")
            add_executable(Simple_equations "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Hard/Simple equations/Simple equations.cpp")
            # Fancy techniques
            add_executable(Bars "Problem solving paradigms/Complete search/Iterative/Fancy techniques/Bars/Bars.cpp")
            add_executable(Zones "Problem solving paradigms/Complete search/Iterative/Fancy techniques/Zones/Zones.cpp")
            add_executable(Grid_game "Problem solving paradigms/Complete search/Iterative/Fancy techniques/Grid game/Grid game.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Fancy techniques/Grid game/util.cpp")
        # Recursive backtracking
            # Easy
            add_executable(The_sultans_successor "Problem solving paradigms/Complete search/Recursive backtracking/Easy/The sultans successor/The sultans successor.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/The sultans successor/utils.cpp")
            add_executable(Call_forwarding "Problem solving paradigms/Complete search/Recursive backtracking/Easy/Call forwarding/Call forwarding.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/Call forwarding/utils.cpp")
            add_executable(The_settlers_of_catan "Problem solving paradigms/Complete search/Recursive backtracking/Easy/The settlers of catan/The settlers of catan.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/The settlers of catan/utils.cpp")
            add_executable(CD "Problem solving paradigms/Complete search/Recursive backtracking/Easy/CD/CD.cpp")
            add_executable(Passwords "Problem solving paradigms/Complete search/Recursive backtracking/Easy/Passwords/Passwords.cpp")
            add_executable(All_walks_of_length_n_from_first_node "Problem solving paradigms/Complete search/Recursive backtracking/Easy/All walks of length n from first node/All walks of length n from first node.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/All walks of length n from first node/utils.cpp")
            add_executable(The_hamming_distance_problem "Problem solving paradigms/Complete search/Recursive backtracking/Easy/The hamming distance problem/The hamming distance problem.cpp")
            add_executable(8_queens_chess_problem "Problem solving paradigms/Complete search/Recursive backtracking/Easy/8 queens chess problem/8 queens chess problem.cpp")
            add_executable(Hanoi_tower_troubles_again "Problem solving paradigms/Complete search/Recursive backtracking/Easy/Hanoi tower troubles again/Hanoi tower troubles again.cpp")
            add_executable(23_out_of_5 "Problem solving paradigms/Complete search/Recursive backtracking/Easy/23 out of 5/23 out of 5.cpp")
            add_executable(Marcus_help "Problem solving paradigms/Complete search/Recursive backtracking/Easy/Marcus help/Marcus help.cpp")
            add_executable(Back_to_the_8_queens "Problem solving paradigms/Complete search/Recursive backtracking/Easy/Back to the 8 queens/Back to the 8 queens.cpp")
            # Medium
            add_executable(Transportation "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Transportation/Transportation.cpp")
            add_executable(Boggle_blitz "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Boggle blitz/Boggle blitz.cpp")
            add_executable(Prime_ring_problem "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Prime ring problem/Prime ring problem.cpp")
            add_executable(Mapping_the_swaps "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Mapping the swaps/Mapping the swaps.cpp")
            IF(NOT APPLE)
            add_executable(Jugs "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Jugs/Jugs.cpp")
            ENDIF()
            add_executable(Sum_it_up "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Sum it up/Sum it up.cpp")
            add_executable(Bundling_newspapers "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Bundling newspapers/Bundling newspapers.cpp")
            add_executable(Hamiltonian_cycle "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Hamiltonian cycle/Hamiltonian cycle.cpp")
            add_executable(Knuths_permutation "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Knuths permutation/Knuths permutation.cpp")
            add_executable(Help_the_leaders "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Help the leaders/Help the leaders.cpp")
            add_executable(The_dominoes_solitaire "Problem solving paradigms/Complete search/Recursive backtracking/Medium/The dominoes solitaire/The dominoes solitaire.cpp")
            add_executable(Bad_code "Problem solving paradigms/Complete search/Recursive backtracking/Medium/Bad code/Bad code.cpp")
            add_executable(The_problem_of_the_crazy_linguist "Problem solving paradigms/Complete search/Recursive backtracking/Medium/The problem of the crazy linguist/The problem of the crazy linguist.cpp")
            add_executable(DNA "Problem solving paradigms/Complete search/Recursive backtracking/Medium/DNA/DNA.cpp")
            # Hard
            add_executable(Graph_coloring "Problem solving paradigms/Complete search/Recursive backtracking/Hard/Graph coloring/Graph coloring.cpp")
            add_executable(Firetruck "Problem solving paradigms/Complete search/Recursive backtracking/Hard/Firetruck/Firetruck.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Hard/Firetruck/utils.cpp")
            add_executable(LED_test "Problem solving paradigms/Complete search/Recursive backtracking/Hard/LED test/LED test.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Hard/LED test/utils.cpp")
            add_executable(Bank_not_quite_OCR "Problem solving paradigms/Complete search/Recursive backtracking/Hard/Bank not quite OCR/Bank not quite OCR.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Hard/Bank not quite OCR/utils.cpp")
    # Divide and conquer
        # Binary search
        add_executable(Dropping_balls "Problem solving paradigms/Divide and conquer/Binary search/Dropping balls/Dropping balls.cpp")
        add_executable(Popes "Problem solving paradigms/Divide and conquer/Binary search/Popes/Popes.cpp")
        add_executable(The_stern_brocot_number_system "Problem solving paradigms/Divide and conquer/Binary search/10077/The Stern Brocot number system.cpp")
        add_executable(Where_is_the_marble "Problem solving paradigms/Divide and conquer/Binary search/10474/Where is the marble.cpp"
                "Problem solving paradigms/Divide and conquer/Binary search/10474/utils.cpp")
        add_executable(Helping_fill_bates "Problem solving paradigms/Divide and conquer/Binary search/10567/Helping Fill Bates.cpp")
        add_executable(The_playboy_chimp "Problem solving paradigms/Divide and conquer/Binary search/10611/The playboy chimp.cpp")
        add_executable(Number_sequence "Problem solving paradigms/Divide and conquer/Binary search/10706/Number sequence.cpp")
        add_executable(The_new_rule_in_euphomia "Problem solving paradigms/Divide and conquer/Binary search/10742/The new rule in Euphomia.cpp"
                "Problem solving paradigms/Divide and conquer/Binary search/10742/utils.cpp")
        add_executable(Exact_sum "Problem solving paradigms/Divide and conquer/Binary search/11057/Exact sum.cpp")
        add_executable(Small_factors "Problem solving paradigms/Divide and conquer/Binary search/11621/Small factors.cpp"
                "Problem solving paradigms/Divide and conquer/Binary search/11621/utils.cpp")
        add_executable(Cantor "Problem solving paradigms/Divide and conquer/Binary search/11701/Cantor.cpp")
        add_executable(N_nod_n "Problem solving paradigms/Divide and conquer/Binary search/11876/N nod n.cpp"
                "Problem solving paradigms/Divide and conquer/Binary search/11876/utils.cpp")
        add_executable(Grapevine "Problem solving paradigms/Divide and conquer/Binary search/12192/Grapevine.cpp"
                "Problem solving paradigms/Divide and conquer/Binary search/12192/utils.cpp")
        # Bisection method or binary search the answer
        add_executable(Solve_it "Problem solving paradigms/Divide and conquer/Bisection method or binary search the answer/10341/Solve it.cpp")
        add_executable(The_monkey_and_the_oiled_bamboo "Problem solving paradigms/Divide and conquer/Bisection method or binary search the answer/12032/The monkey and the oiled bamboo.cpp")
        add_executable(Through_the_desert "Problem solving paradigms/Divide and conquer/Bisection method or binary search the answer/11935/Through the desert.cpp")
        # Other divide & conquer problems
        add_executable(Bit_maps "Problem solving paradigms/Divide and conquer/Other divide & conquer problems/183/Bit maps.cpp")
    # Greedy
        # Classical
        add_executable(Station_balance "Problem solving paradigms/Greedy/Classical/410/Station balance.cpp"
                utils/print.cpp)
        add_executable(Radar_installation "Problem solving paradigms/Greedy/Classical/1193/Radar installation.cpp"
                utils/print.cpp)
        add_executable(Minimal_coverage "Problem solving paradigms/Greedy/Classical/10020/Minimal coverage.cpp"
                "Problem solving paradigms/Greedy/Classical/10020/utils.cpp")
        add_executable(Watering_grass "Problem solving paradigms/Greedy/Classical/10382/Watering grass.cpp")
        add_executable(The_bus_driver_problem "Problem solving paradigms/Greedy/Classical/11389/The bus driver problem.cpp")
        add_executable(Coin_collector "Problem solving paradigms/Greedy/Classical/11264/Coin collector.cpp")