cmake_minimum_required(VERSION 3.8)
project(UVa)

set(CMAKE_CXX_STANDARD 11)

find_package(Java REQUIRED)
include(UseJava)

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
        # Anagram
        add_executable(Anagram "Introduction/Ad hoc/Anagram/195/Anagram.cpp")
        add_executable(Anagrams "Introduction/Ad hoc/Anagram/454/Anagrams.cpp")
        add_executable(Ananagrams "Introduction/Ad hoc/Anagram/156/Ananagrams.cpp")
        # Card
        add_executable(Bridge_hand_evaluator "Introduction/Ad hoc/Card/462/Bridge hand evaluator.cpp")
        add_executable(What_is_the_card "Introduction/Ad hoc/Card/10646/What is the card.cpp")
        add_executable(Jollo "Introduction/Ad hoc/Card/12247/Jollo.cpp")
        # Chess
        add_executable(Chess "Introduction/Ad hoc/Chess/278/Chess.cpp")
        add_executable(Chessboard_in_fen "Introduction/Ad hoc/Chess/10284/Chessboard in FEN.cpp")
        add_executable(How_many_knights "Introduction/Ad hoc/Chess/696/How many knights.cpp")
        # Others
        add_executable(Bowling "Introduction/Ad hoc/Others/584/Bowling.cpp")
        add_executable(Hangman_judge "Introduction/Ad hoc/Others/489/Hangman judge.cpp")
        add_executable(Minesweeper "Introduction/Ad hoc/Others/10189/Minesweeper.cpp")
        add_executable(Snakes_and_ladders "Introduction/Ad hoc/Others/11459/Snakes and ladders.cpp")
        add_executable(Traditional_BINGO "Introduction/Ad hoc/Others/10813/Traditional BINGO.cpp")
        # Palindrome
        add_executable(Magic_square_palindromes "Introduction/Ad hoc/Palindrome/11221/Magic square palindromes.cpp")
        add_executable(Mother_bear "Introduction/Ad hoc/Palindrome/10945/Mother bear.cpp")
        add_executable(Palindromes "Introduction/Ad hoc/Palindrome/401/Palindromes.cpp")
        # Real life problems
        add_executable(Beat_the_spread "Introduction/Ad hoc/Real life problems/10812/Beat the spread.cpp")
        add_executable(Boolket_printing "Introduction/Ad hoc/Real life problems/637/Booklet printing.cpp")
        add_executable(Consanguine_calculations "Introduction/Ad hoc/Real life problems/1061/Consanguine calculations.cpp"
                "Introduction/Ad hoc/Real life problems/1061/utils.cpp")
        add_executable(Counterfeit_dollar "Introduction/Ad hoc/Real life problems/608/Counterfeit dollar.cpp")
        add_executable(Postscript "Introduction/Ad hoc/Real life problems/403/Postscript.cpp"
                "Introduction/Ad hoc/Real life problems/403/util.cpp")
        add_executable(Traffic_lights "Introduction/Ad hoc/Real life problems/161/Traffic lights.cpp"
                "Introduction/Ad hoc/Real life problems/161/utils.cpp")
        # Time
        add_executable(Clock_hands "Introduction/Ad hoc/Time/579/Clock hands.cpp")
        add_jar(Cancer_or_scorpio "Introduction/Ad hoc/Time/11947/Cancer or scorpio/src/Main.java")
        add_jar(Y3k "Introduction/Ad hoc/Time/893/Y3K/src/Main.java")
        # Time waster problems
        add_executable(All_integer_average "Introduction/Ad hoc/Time waster problems/12060/All integer average.cpp")
        add_executable(Mobile_casanova "Introduction/Ad hoc/Time waster problems/12085/Mobile casanova.cpp")

# Data structures and libraries
    # Linear DS builtin lib
        # 1D array manipulation
        add_executable(Army_buddies "Data structures and libraries/Linear DS builtin lib/1D array manipulation/12356/Army buddies.cpp")
        add_executable(Jolly_jumpers "Data structures and libraries/Linear DS builtin lib/1D array manipulation/10038/Jolly jumpers.cpp")
        add_executable(Newspaper "Data structures and libraries/Linear DS builtin lib/1D array manipulation/11340/Newspaper.cpp")
        # 2D array manipulation
        add_executable(Grid_successor "Data structures and libraries/Linear DS builtin lib/2D array manipulation/11581/Grid successor.cpp")
        add_executable(Rotated_squares "Data structures and libraries/Linear DS builtin lib/2D array manipulation/10855/Rotated squares.cpp")
        add_executable(Spiral_tap "Data structures and libraries/Linear DS builtin lib/2D array manipulation/10920/Spiral tap.cpp")
        # Bit manipulation
        add_executable(Multitasking "Data structures and libraries/Linear DS builtin lib/Bit manipulation/11926/Multitasking.cpp")
        add_executable(Splitting_numbers "Data structures and libraries/Linear DS builtin lib/Bit manipulation/11933/Splitting numbers.cpp")
        # C++ STL algorithm
        add_executable(Content_scoreboard "Data structures and libraries/Linear DS builtin lib/C++ STL algorithm/10258/Contest scoreboard.cpp")
        add_executable(ID_codes "Data structures and libraries/Linear DS builtin lib/C++ STL algorithm/146/ID codes.cpp")
        add_executable(What_is_the_median "Data structures and libraries/Linear DS builtin lib/C++ STL algorithm/10107/What is the median.cpp")
        # C++ STL list
        add_executable(Broken_keyboard "Data structures and libraries/Linear DS builtin lib/C++ STL list/11988/Broken keyboard.cpp")
        # C++ STL queue and deque
        add_executable(Frerry_loading_III "Data structures and libraries/Linear DS builtin lib/C++ STL queue and deque/10901/Ferry loading III.cpp")
        add_executable(Ferry_loading_IV "Data structures and libraries/Linear DS builtin lib/C++ STL queue and deque/11034/Ferry loading IV.cpp")
        add_executable(The_lonesome_cargo_distributor "Data structures and libraries/Linear DS builtin lib/C++ STL queue and deque/10172/The lonesome cargo distributor.cpp")
        # C++ STL stack
        add_executable(Anagrams_by_stack "Data structures and libraries/Linear DS builtin lib/C++ STL stack/732/Anagrams by stack.cpp")
        add_executable(Rails "Data structures and libraries/Linear DS builtin lib/C++ STL stack/514/Rails.cpp")
    # Non linear DS builtin lib
        # C++ STL map
        add_executable(Conformity "Data structures and libraries/Non linear DS builtin lib/C++ STL map/11286/Conformity.cpp")
        add_executable(Hardwood_species "Data structures and libraries/Non linear DS builtin lib/C++ STL map/10226/Hardwood species.cpp")
        add_executable(Unique_snowflakes "Data structures and libraries/Non linear DS builtin lib/C++ STL map/11572/Unique snowflakes.cpp")
        # C++ STL priority_queue
        add_executable(Add_all "Data structures and libraries/Non linear DS builtin lib/C++ STL priority_queue/10954/Add all.cpp")
        add_executable(Argus "Data structures and libraries/Non linear DS builtin lib/C++ STL priority_queue/1203/Argus.cpp")
        add_executable(I_can_guess_the_data_structure "Data structures and libraries/Non linear DS builtin lib/C++ STL priority_queue/11995/I can guess the data structure.cpp")
        # C++ STL set
        add_executable(CD_stl_set "Data structures and libraries/Non linear DS builtin lib/C++ STL set/11849/CD.cpp")
        add_executable(Hoax_or_what "Data structures and libraries/Non linear DS builtin lib/C++ STL set/11136/Hoax or what.cpp")
        add_executable(Lemmings_battle "Data structures and libraries/Non linear DS builtin lib/C++ STL set/978/Lemmings battle.cpp")
    # DS with our own lib
        # Graph
        add_executable(Easy_problem_from_rujia_liu "Data structures and libraries/DS with our own lib/Graph/11991/Easy problem from rujia liu.cpp")
        add_executable(Matrix_transpose "Data structures and libraries/DS with our own lib/Graph/10895/Matrix transpose.cpp"
                "Data structures and libraries/DS with our own lib/Graph/10895/utils.cpp")
        add_executable(The_forest_for_the_trees "Data structures and libraries/DS with our own lib/Graph/599/The forest for the trees.cpp")
        # Tree-related DS
        add_executable(Ahoy_pirates "Data structures and libraries/DS with our own lib/Tree-related DS/11402/Ahoy pirates.cpp")
        add_executable(Frequent_values "Data structures and libraries/DS with our own lib/Tree-related DS/11235/Frequent values.cpp"
                "Data structures and libraries/DS with our own lib/Tree-related DS/11235/utils.cpp")
        add_executable(Interval_product "Data structures and libraries/DS with our own lib/Tree-related DS/12532/Interval product.cpp")
        # Union-find disjoint sets
        add_executable(Network_connections "Data structures and libraries/DS with our own lib/Union-find disjoint sets/793/Network connections.cpp")
        add_executable(Virtual_friends "Data structures and libraries/DS with our own lib/Union-find disjoint sets/11503/Virtual friends.cpp"
                "Data structures and libraries/DS with our own lib/Union-find disjoint sets/11503/utils.cpp")
        add_executable(Waking_up_brain "Data structures and libraries/DS with our own lib/Union-find disjoint sets/10507/Waking up brain.cpp"
                "Data structures and libraries/DS with our own lib/Union-find disjoint sets/11503/utils.cpp")

# Problem solving paradigms
    # Complete search
        # Iterative
            # Linear scan
            add_executable(Integer_sequence_from "Problem solving paradigms/Complete search/Iterative/Linear scan/927/Integer sequence from.cpp")
            add_executable(Expert_enough "Problem solving paradigms/Complete search/Iterative/Linear scan/1237/Expert enough.cpp")
            add_executable(Fractions_again "Problem solving paradigms/Complete search/Iterative/Linear scan/10976/Fractions again.cpp")
            # Two nested loops
            add_executable(Sales "Problem solving paradigms/Complete search/Iterative/Two nested loops/1260/Sales.cpp")
            add_executable(Closest_sums "Problem solving paradigms/Complete search/Iterative/Two nested loops/10487/Closest sums.cpp")
            add_executable(Tour_de_france "Problem solving paradigms/Complete search/Iterative/Two nested loops/11242/Tour de france.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Two nested loops/11242/utils.cpp")
            # Three or more nested loops
            add_executable(Lotto "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/441/Lotto.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/441/utils.cpp")
            add_executable(Dart_a_mania "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/735/Dart-a-mania.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/735/utils.cpp")
            add_executable(The_path_in_the_colored_field "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/10102/The path in the colored field.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Easy/10102/utils.cpp")
            add_executable(Simple_equations "Problem solving paradigms/Complete search/Iterative/Three or more nested loops/Hard/11565/Simple equations.cpp")
            # Fancy techniques
            add_executable(Bars "Problem solving paradigms/Complete search/Iterative/Fancy techniques/12455/Bars.cpp")
            add_executable(Zones "Problem solving paradigms/Complete search/Iterative/Fancy techniques/1047/Zones.cpp")
            add_executable(Grid_game "Problem solving paradigms/Complete search/Iterative/Fancy techniques/11553/Grid game.cpp"
                    "Problem solving paradigms/Complete search/Iterative/Fancy techniques/11553/util.cpp")
        # Recursive backtracking
            # Easy
            add_executable(The_sultans_successor "Problem solving paradigms/Complete search/Recursive backtracking/Easy/167/The sultans successor.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/167/utils.cpp")
            add_executable(Call_forwarding "Problem solving paradigms/Complete search/Recursive backtracking/Easy/380/Call forwarding.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/380/utils.cpp")
            add_executable(The_settlers_of_catan "Problem solving paradigms/Complete search/Recursive backtracking/Easy/539/The settlers of catan.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/539/utils.cpp")
            add_executable(CD "Problem solving paradigms/Complete search/Recursive backtracking/Easy/624/CD.cpp")
            add_executable(Passwords "Problem solving paradigms/Complete search/Recursive backtracking/Easy/628/Passwords.cpp")
            add_executable(All_walks_of_length_n_from_first_node "Problem solving paradigms/Complete search/Recursive backtracking/Easy/677/All walks of length n from first node.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Easy/677/utils.cpp")
            add_executable(The_hamming_distance_problem "Problem solving paradigms/Complete search/Recursive backtracking/Easy/729/The hamming distance problem.cpp")
            add_executable(8_queens_chess_problem "Problem solving paradigms/Complete search/Recursive backtracking/Easy/750/8 queens chess problem.cpp")
            add_executable(Hanoi_tower_troubles_again "Problem solving paradigms/Complete search/Recursive backtracking/Easy/10276/Hanoi tower troubles again.cpp")
            add_executable(23_out_of_5 "Problem solving paradigms/Complete search/Recursive backtracking/Easy/10344/23 out of 5.cpp")
            add_executable(Marcus_help "Problem solving paradigms/Complete search/Recursive backtracking/Easy/10452/Marcus help.cpp")
            add_executable(Back_to_the_8_queens "Problem solving paradigms/Complete search/Recursive backtracking/Easy/11085/Back to the 8 queens.cpp")
            # Medium
            add_executable(Transportation "Problem solving paradigms/Complete search/Recursive backtracking/Medium/301/Transportation.cpp")
            add_executable(Boggle_blitz "Problem solving paradigms/Complete search/Recursive backtracking/Medium/487/Boggle blitz.cpp")
            add_executable(Prime_ring_problem "Problem solving paradigms/Complete search/Recursive backtracking/Medium/524/Prime ring problem.cpp")
            add_executable(Mapping_the_swaps "Problem solving paradigms/Complete search/Recursive backtracking/Medium/331/Mapping the swaps.cpp")
            IF(WIN32)
            add_executable(Jugs "Problem solving paradigms/Complete search/Recursive backtracking/Medium/571/Jugs.cpp")
            ENDIF()
            add_executable(Sum_it_up "Problem solving paradigms/Complete search/Recursive backtracking/Medium/574/Sum it up.cpp")
            add_executable(Bundling_newspapers "Problem solving paradigms/Complete search/Recursive backtracking/Medium/598/Bundling newspapers.cpp")
            add_executable(Hamiltonian_cycle "Problem solving paradigms/Complete search/Recursive backtracking/Medium/775/Hamiltonian cycle.cpp")
            add_executable(Knuths_permutation "Problem solving paradigms/Complete search/Recursive backtracking/Medium/10063/Knuths permutation.cpp")
            add_executable(Help_the_leaders "Problem solving paradigms/Complete search/Recursive backtracking/Medium/10475/Help the leaders.cpp")
            add_executable(The_dominoes_solitaire "Problem solving paradigms/Complete search/Recursive backtracking/Medium/10503/The dominoes solitaire.cpp")
            add_executable(Bad_code "Problem solving paradigms/Complete search/Recursive backtracking/Medium/10950/Bad code.cpp")
            add_executable(The_problem_of_the_crazy_linguist "Problem solving paradigms/Complete search/Recursive backtracking/Medium/11201/The problem of the crazy linguist.cpp")
            add_executable(DNA "Problem solving paradigms/Complete search/Recursive backtracking/Medium/11961/DNA.cpp")
            # Hard
            add_executable(Graph_coloring "Problem solving paradigms/Complete search/Recursive backtracking/Hard/193/Graph coloring.cpp")
            add_executable(Firetruck "Problem solving paradigms/Complete search/Recursive backtracking/Hard/208/Firetruck.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Hard/208/utils.cpp")
            add_executable(LED_test "Problem solving paradigms/Complete search/Recursive backtracking/Hard/416/LED test.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Hard/416/utils.cpp")
            add_executable(Bank_not_quite_OCR "Problem solving paradigms/Complete search/Recursive backtracking/Hard/433/Bank not quite OCR.cpp"
                    "Problem solving paradigms/Complete search/Recursive backtracking/Hard/433/utils.cpp")
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
                "utils/print.cpp")
        add_executable(Radar_installation "Problem solving paradigms/Greedy/Classical/1193/Radar installation.cpp"
                "utils/print.cpp")
        add_executable(Minimal_coverage "Problem solving paradigms/Greedy/Classical/10020/Minimal coverage.cpp"
                "Problem solving paradigms/Greedy/Classical/10020/utils.cpp")
        add_executable(Watering_grass "Problem solving paradigms/Greedy/Classical/10382/Watering grass.cpp")
        add_executable(The_bus_driver_problem "Problem solving paradigms/Greedy/Classical/11389/The bus driver problem.cpp")
        add_executable(Coin_collector "Problem solving paradigms/Greedy/Classical/11264/Coin collector.cpp")
        add_executable(Gas_stations "Problem solving paradigms/Greedy/Classical/12321/Gas stations.cpp")
        add_executable(Scarecrow "Problem solving paradigms/Greedy/Classical/12405/Scarecrow.cpp")
        # Involving sorting
        add_executable(Bridge "Problem solving paradigms/Greedy/Involving sorting/10037/Bridge.cpp")
        add_executable(The_grand_dinner "Problem solving paradigms/Greedy/Involving sorting/10249/The grand dinner.cpp")
        add_executable(Foriegn_exchange "Problem solving paradigms/Greedy/Involving sorting/10763/Foreign exchange.cpp")
        add_executable(The_mad_numerologist "Problem solving paradigms/Greedy/Involving sorting/10785/The mad numerologist.cpp")
        add_executable(The_trip_2007 "Problem solving paradigms/Greedy/Involving sorting/11100/The trip 2007.cpp")
        add_executable(The_dragon_of_loowater "Problem solving paradigms/Greedy/Involving sorting/11292/The dragon of loowater.cpp")
        add_executable(Shopaholic "Problem solving paradigms/Greedy/Involving sorting/11369/Shopaholic.cpp")
        add_executable(Commando_war "Problem solving paradigms/Greedy/Involving sorting/11729/Commando war.cpp")
        add_executable(Boiled_eggs "Problem solving paradigms/Greedy/Involving sorting/11900/Boiled eggs.cpp")
        add_executable(A_match_making_problem "Problem solving paradigms/Greedy/Involving sorting/12210/A match making problem.cpp"
                "utils/print.cpp")
    # Dynamic programming
        # Max 1D range sum
        add_executable(Jill_rides_again "Problem solving paradigms/Dynamic programming/Max 1D range sum/507/Jill rides again.cpp")
        add_jar(Max_sub_sequence_product "Problem solving paradigms/Dynamic programming/Max 1D range sum/787/Max sub-sequence product/src/Main.java")
        add_executable(The_jackpot "Problem solving paradigms/Dynamic programming/Max 1D range sum/10684/The jackpot.cpp")
        # Max 2D range sum
        add_executable(Maximum_sum "Problem solving paradigms/Dynamic programming/Max 2D range sum/108/Maximum sum.cpp"
                "utils/print.cpp")
        add_executable(Largest_submatrix "Problem solving paradigms/Dynamic programming/Max 2D range sum/836/Largest submatrix.cpp"
                "utils/print.cpp")
        add_executable(Localized_summing_for_blurring "Problem solving paradigms/Dynamic programming/Max 2D range sum/983/Localized summing for blurring.cpp"
                "utils/print.cpp")
        add_executable(Take_the_land "Problem solving paradigms/Dynamic programming/Max 2D range sum/10074/Take the land.cpp"
                "utils/print.cpp")
        add_executable(Largest_block "Problem solving paradigms/Dynamic programming/Max 2D range sum/10667/Largest block.cpp"
                "utils/print.cpp")
        add_executable(Maximum_sum_on_a_torus "Problem solving paradigms/Dynamic programming/Max 2D range sum/10827/Maximum sum on a torus.cpp"
                "utils/print.cpp")
        add_executable(Area "Problem solving paradigms/Dynamic programming/Max 2D range sum/11951/Area.cpp"
                "utils/print.cpp")
        # Longest increasing subsequence
        add_executable(History_grading "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/111/History grading.cpp")
        add_executable(Testing_the_catcher "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/231/Testing the catcher.cpp")
        add_executable(What_goes_up "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/481/What goes up.cpp")
        add_executable(Strategic_defense_initiative "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/497/Strategic defense initiative.cpp")
        add_executable(Tiling_up_blocks "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/1196/Tiling up blocks.cpp")
        add_executable(Is_bigger_smarter "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/10131/Is bigger smarter.cpp")
        add_executable(Wavio_sequence "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/10534/Wavio sequence.cpp"
                "utils/print.cpp")
        # 0-1 Knapsack
        add_executable(Dividing_coins "Problem solving paradigms/Dynamic programming/0-1 Knapsack/562/Dividing coins.cpp"
                utils/print.cpp)
        add_executable(Diving_for_gold "Problem solving paradigms/Dynamic programming/0-1 Knapsack/990/Diving for gold.cpp"
                utils/print.cpp)