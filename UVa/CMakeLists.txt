cmake_minimum_required(VERSION 3.8)
project(UVa)

set(CMAKE_CXX_STANDARD 17)

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
        # TODO : Compilation fails for The_playboy_chimp because it uses bind2nd, which is deprecated in C++ 17
        # add_executable(The_playboy_chimp "Problem solving paradigms/Divide and conquer/Binary search/10611/The playboy chimp.cpp")
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
        add_executable(The_tower_of_babylon "Problem solving paradigms/Dynamic programming/Longest increasing subsequence/437/The tower of babylon.cpp")
        # 0-1 Knapsack
        add_executable(Dividing_coins "Problem solving paradigms/Dynamic programming/0-1 Knapsack/562/Dividing coins.cpp"
                utils/print.cpp)
        add_executable(Diving_for_gold "Problem solving paradigms/Dynamic programming/0-1 Knapsack/990/Diving for gold.cpp"
                utils/print.cpp)
        add_executable(Sum_of_different_primes "Problem solving paradigms/Dynamic programming/0-1 Knapsack/1213/Sum of different primes.cpp")
        add_executable(Supersale "Problem solving paradigms/Dynamic programming/0-1 Knapsack/10130/SuperSale.cpp")
        add_executable(Ferry_loading "Problem solving paradigms/Dynamic programming/0-1 Knapsack/10261/Ferry loading.cpp")
        add_executable(Divisible_group_sums "Problem solving paradigms/Dynamic programming/0-1 Knapsack/10616/Divisible group sums.cpp")
        add_executable(Luggage "Problem solving paradigms/Dynamic programming/0-1 Knapsack/10664/Luggage.cpp")
        add_executable(Trouble_of_13_dots "Problem solving paradigms/Dynamic programming/0-1 Knapsack/10819/Trouble of 13 dots.cpp")
        add_executable(Boxes "Problem solving paradigms/Dynamic programming/0-1 Knapsack/11003/Boxes.cpp")
        add_executable(Lets_yum_cha "Problem solving paradigms/Dynamic programming/0-1 Knapsack/11566/Lets yum cha.cpp")
        add_executable(Best_coalitions "Problem solving paradigms/Dynamic programming/0-1 Knapsack/11658/Best coalitions.cpp")
        # Coin change
        add_executable(Dollars "Problem solving paradigms/Dynamic programming/Coin change/147/Dollars.cpp")
        add_executable(Making_change "Problem solving paradigms/Dynamic programming/Coin change/166/Making change.cpp")
        add_executable(Let_me_count_the_ways "Problem solving paradigms/Dynamic programming/Coin change/357/Let me count the ways.cpp")
        add_executable(Coin_change "Problem solving paradigms/Dynamic programming/Coin change/674/Coin change.cpp")
        add_executable(e_coins "Problem solving paradigms/Dynamic programming/Coin change/10306/e-Coins.cpp")
        add_executable(Pay_the_price "Problem solving paradigms/Dynamic programming/Coin change/10313/Pay the price.cpp")
        add_executable(Ingenuous_cubrency "Problem solving paradigms/Dynamic programming/Coin change/11137/Ingenuous cubrency.cpp")        
        add_executable(Exact_change "Problem solving paradigms/Dynamic programming/Coin change/11517/Exact change.cpp")
        # Traveling salesman problem
        add_executable(Collecting_beepers "Problem solving paradigms/Dynamic programming/Traveling salesman problem/10496/Collecting beepers.cpp"
                "utils/print.cpp")
        add_executable(Getting_in_line "Problem solving paradigms/Dynamic programming/Traveling salesman problem/216/Getting in line.cpp"
                "utils/print.cpp")
        # Non classical
        add_executable(Unidirectional_TSP "Problem solving paradigms/Dynamic programming/Non classical/116/Unidirectional TSP.cpp")
        add_executable(Spreadsheet "Problem solving paradigms/Dynamic programming/Non classical/196/Spreadsheet.cpp")
        add_executable(String_popping "Problem solving paradigms/Dynamic programming/Non classical/1261/String popping.cpp")
        add_executable(Cutting_sticks "Problem solving paradigms/Dynamic programming/Non classical/10003/Cutting sticks.cpp")
        add_executable(Divisibility "Problem solving paradigms/Dynamic programming/Non classical/10036/Divisibility.cpp")
        add_executable(Game_show_math "Problem solving paradigms/Dynamic programming/Non classical/10400/Game show math.cpp")
        add_executable(The_marriage_interview "Problem solving paradigms/Dynamic programming/Non classical/10446/The marriage interview.cpp")
        add_executable(Homer_simpson "Problem solving paradigms/Dynamic programming/Non classical/10465/Homer simpson.cpp")
        add_executable(Marks_distribution "Problem solving paradigms/Dynamic programming/Non classical/10910/Marks distribution.cpp")
        add_executable(Simple_minded_hashing "Problem solving paradigms/Dynamic programming/Non classical/10912/Simple minded hashing.cpp")
        add_executable(How_do_you_add "Problem solving paradigms/Dynamic programming/Non classical/10943/How do you add.cpp")
        add_executable(Lowest_price_in_town "Problem solving paradigms/Dynamic programming/Non classical/10980/Lowest price in town.cpp")
        add_executable(A_grouping_problem "Problem solving paradigms/Dynamic programming/Non classical/11026/A grouping problem.cpp"
                "utils/print.cpp")
        add_executable(Squares "Problem solving paradigms/Dynamic programming/Non classical/11407/Squares.cpp")
        add_executable(Chest_of_drawers "Problem solving paradigms/Dynamic programming/Non classical/11420/Chest of drawers.cpp")
        add_jar(Chest_of_drawers_java "Problem solving paradigms/Dynamic programming/Non classical/11420/Chest of drawers/src/Main.java")
        add_executable(Wedding_shopping "Problem solving paradigms/Dynamic programming/Non classical/11450/Wedding shopping.cpp")
        add_executable(Sqrt_log_sin "Problem solving paradigms/Dynamic programming/Non classical/11703/Sqrt log sin.cpp")
        add_executable(Bar_codes "Problem solving paradigms/Dynamic programming/Non classical/10721/Bar codes.cpp")
        add_executable(Test_the_rods "Problem solving paradigms/Dynamic programming/Non classical/10086/Test the rods.cpp")

# Graph
        # Graph traversal
                # Just graph traversal
                add_executable(Dominator "Graph/Graph traversal/Just graph traversal/11902/Dominator.cpp")
                add_executable(Mutant_flatworld_explorers "Graph/Graph traversal/Just graph traversal/118/Mutant flatworld explorers.cpp")
                add_executable(Theseus_and_the_minotaur "Graph/Graph traversal/Just graph traversal/168/Theseus and the minotaur.cpp")
                add_executable(Vertex "Graph/Graph traversal/Just graph traversal/280/Vertex.cpp")
                add_executable(Mapping_the_route "Graph/Graph traversal/Just graph traversal/614/Mapping the route.cpp")
                add_executable(Forwarding_emails "Graph/Graph traversal/Just graph traversal/12442/Forwarding emails.cpp")
                add_executable(As_long_as_I_learn_I_live "Graph/Graph traversal/Just graph traversal/12376/As long as I learn I live.cpp")
                add_executable(Wedding_of_sultan "Graph/Graph traversal/Just graph traversal/12582/Wedding of sultan.cpp")
                # Flood fill
                add_executable(Graph_connectivity "Graph/Graph traversal/Flood fill/459/Graph connectivity.cpp")
                add_executable(Il_gioco_dell_x "Graph/Graph traversal/Flood fill/260/Il gioco dell x.cpp")
                add_executable(The_seasonal_war "Graph/Graph traversal/Flood fill/352/The seasonal war.cpp")
                add_executable(Wetlands_of_florida "Graph/Graph traversal/Flood fill/469/Wetlands of florida.cpp")
                add_executable(Deciding_victory_in_go "Graph/Graph traversal/Flood fill/852/Deciding victory in go.cpp")
                add_executable(2D_nim "Graph/Graph traversal/Flood fill/10707/2D nim.cpp")
                add_executable(Getting_gold "Graph/Graph traversal/Flood fill/11561/Getting gold.cpp")
                add_executable(Poor_trade_advisor "Graph/Graph traversal/Flood fill/11749/Poor trade advisor.cpp")
                add_executable(Battleships "Graph/Graph traversal/Flood fill/11953/Battleships.cpp")
                # Topological sort
                add_executable(Ordering_tasks "Graph/Graph traversal/Topological sort/10305/Ordering tasks.cpp")
                add_executable(Beverages "Graph/Graph traversal/Topological sort/11060/Beverages.cpp")
                add_executable(Pick_up_sticks "Graph/Graph traversal/Topological sort/11686/Pick up sticks.cpp")
                add_executable(Following_orders "Graph/Graph traversal/Topological sort/124/Following orders.cpp")
                # Bipartite graph check
                add_executable(Bicoloring "Graph/Graph traversal/Bipartite graph check/10004/Bicoloring.cpp")
                add_executable(Montesco_vs_capuleto "Graph/Graph traversal/Bipartite graph check/10505/Montesco vs capuleto.cpp")
                add_executable(Place_the_guards "Graph/Graph traversal/Bipartite graph check/11080/Place the guards.cpp")
                # Finding articulation points, bridges
                add_executable(Network "Graph/Graph traversal/Finding articulation points, bridges/315/Network.cpp")
                add_executable(Street_directions "Graph/Graph traversal/Finding articulation points, bridges/610/Street directions.cpp")
                add_executable(Critical_links "Graph/Graph traversal/Finding articulation points, bridges/796/Critical links.cpp")
                add_executable(Doves_and_bombs "Graph/Graph traversal/Finding articulation points, bridges/10765/Doves and bombs.cpp")
        # Minimum spanning tree
                # Standard
                add_executable(Re-connecting_computer_sites "Graph/Minimum spanning tree/Standard/908/Re-connecting computer sites.cpp")
                add_executable(Anti_brute_force_lock "Graph/Minimum spanning tree/Standard/1235/Anti brute force lock.cpp")
                add_executable(Transportation_system "Graph/Minimum spanning tree/Standard/11228/Transportation system.cpp")
                add_executable(Airports "Graph/Minimum spanning tree/Standard/11733/Airports.cpp")
                add_executable(Heavy_cycle_edges "Graph/Minimum spanning tree/Standard/11747/Heavy cycle edges.cpp")
                # Variants
                add_executable(Frogger "Graph/Minimum spanning tree/Variants/534/Frogger.cpp")
                add_executable(X-plosives "Graph/Minimum spanning tree/Variants/1160/X-plosives.cpp")
                add_executable(The_bug_sensor_problem "Graph/Minimum spanning tree/Variants/1216/The bug sensor problem.cpp")
                add_executable(The_tourist_guide "Graph/Minimum spanning tree/Variants/10099/The tourist guide.cpp")
                add_executable(Highways "Graph/Minimum spanning tree/Variants/10147/Highways.cpp")
                add_executable(Is_there_a_second_way_left "Graph/Minimum spanning tree/Variants/10462/Is there a second way left.cpp")
        # Single source shortest paths
                # On unweighted graph : BFS, easier
                add_executable(A_node_too_far "Graph/Single source shortest paths/336/A node too far.cpp")
                add_executable(Word_transformation "Graph/Single source shortest paths/429/Word transformation.cpp")
                add_executable(The_net "Graph/Single source shortest paths/627/The net.cpp")
                add_executable(Bombs_no_they_are_mines "Graph/Single source shortest paths/10653/Bombs no they are mines.cpp")
                # On unweighted graph : BSF, harder
                add_executable(Fire "Graph/Single source shortest paths/11624/Fire.cpp")
                # On weighted graph : Dijkstra's, easier
                add_executable(Number_maze "Graph/Single source shortest paths/929/Number maze.cpp")
                add_executable(Mice_and_maze "Graph/Single source shortest paths/1112/Mice and maze.cpp")
                # On unweighted graph : Dijkstra's, harder
                add_executable(Travel "Graph/Single source shortest paths/10166/Travel.cpp")
                add_executable(Fire_station "Graph/Single source shortest paths/10278/Fire station.cpp")
                add_executable(Rough_roads "Graph/Single source shortest paths/10356/Rough roads.cpp")
                add_executable(Fill "Graph/Single source shortest paths/10603/Fill.cpp")
                add_executable(Lift_hopping "Graph/Single source shortest paths/10801/Lift hopping.cpp")
                add_executable(Fuel_tank "Graph/Single source shortest paths/11367/Fuel tank.cpp")
                add_executable(Airport_setup "Graph/Single source shortest paths/11377/Airport setup.cpp")
                add_executable(Babel "Graph/Single source shortest paths/11492/Babel.cpp")
                add_executable(Route_change "Graph/Single source shortest paths/11833/Route change.cpp")
                add_executable(Highest_paid_toll "Graph/Single source shortest paths/12047/Highest paid toll.cpp")
                # On negative weight cycle : Bellman Ford
                add_executable(Wormholes "Graph/Single source shortest paths/558/Wormholes.cpp")
                add_executable(Traffic "Graph/Single source shortest paths/10449/Traffic.cpp")
                add_executable(Xyzzy "Graph/Single source shortest paths/10557/Xyzzy.cpp")
        # All pairs shortest paths
                # Floyd Warshall's standard application
                add_executable(Non_stop_travel "Graph/All pairs shortest paths/341/Non stop travel.cpp")
                add_executable(Interstar_transport "Graph/All pairs shortest paths/1247/Interstar transport.cpp")
                add_executable(Meeting_prof_Miguel "Graph/All pairs shortest paths/10171/Meeting prof Miguel.cpp")
                add_executable(Avoiding_your_boss "Graph/All pairs shortest paths/10354/Avoiding your boss.cpp")
                add_executable(Commandos "Graph/All pairs shortest paths/11463/Commandos.cpp")
                add_jar(Arbitrage "Graph/All pairs shortest paths/104/Arbitrage/src/Arbitrage.java")
                add_executable(Numbering_paths "Graph/All pairs shortest paths/125/Numbering paths.cpp")
                add_executable(Cat_and_mouse "Graph/All pairs shortest paths/274/Cat and mouse.cpp")
                add_jar(Arbitrage_II "Graph/All pairs shortest paths/436/src/Main.java")
                add_executable(Identifying_concurrent_events "Graph/All pairs shortest paths/334/Identifying concurrent events.cpp")
                add_executable(No_more_prerequisites_please "Graph/All pairs shortest paths/925/No more prerequisites please.cpp")
                add_executable(Degrees_of_separation "Graph/All pairs shortest paths/1056/Degrees of separation.cpp")
        # Network flow
                # Standard max flow problem (Edmonds Karp's)
                add_executable(Software_allocation "Graph/Network flow/259/Software allocation.cpp")
                add_executable(My_T_shirt_suits_me "Graph/Network flow/11045/My T shirt suits me.cpp")
                add_executable(Clever_naming_patterns "Graph/Network flow/11418/Clever naming patterns.cpp")
                # Variants
                add_executable(Power_transmission "Graph/Network flow/10330/Power transmission.cpp")
                add_executable(Sabotage "Graph/Network flow/10480/Sabotage.cpp")
        # Special graphs
                # Single source shortest/longest path on DAG
                add_executable(Stacking_boxes "Graph/Special graphs/103/Stacking boxes.cpp")
                add_executable(Project_scheduling "Graph/Special graphs/452/Project scheduling.cpp")
                add_executable(Hippity_hopscotch "Graph/Special graphs/10259/Hippity hopscotch.cpp")
                # Counting paths in DAG
                add_executable(Walking_on_the_safe_side "Graph/Special graphs/825/Walking on the safe side.cpp")
                add_executable(Many_paths_one_destination "Graph/Special graphs/988/Many paths one destination.cpp")
                add_executable(Injured_queen_problem "Graph/Special graphs/10401/Injured queen problem.cpp")
                # Converting general graph to DAG
                add_executable(Always_on_the_run "Graph/Special graphs/590/Always on the run.cpp")
                add_executable(Winterim_backpacking_trip "Graph/Special graphs/907/Winterim backpacking trip.cpp")
                add_executable(TV_game "Graph/Special graphs/910/TV game.cpp")
                add_executable(Traveling_politician "Graph/Special graphs/10543/Traveling politician.cpp")
                add_executable(Travelling_salesman "Graph/Special graphs/10702/Travelling salesman.cpp")
                add_executable(Segments "Graph/Special graphs/10874/Segments.cpp")
                add_executable(Walking_on_a_grid "Graph/Special graphs/10913/Walking on a grid.cpp")
                add_executable(Gathering_food "Graph/Special graphs/11487/Gathering food.cpp")
                # Trees
                add_executable(Climbing_trees "Graph/Special graphs/115/Climbing trees.cpp")
                add_executable(Tree_recovery "Graph/Special graphs/536/Tree recovery.cpp")
                add_executable(The_falling_leaves "Graph/Special graphs/699/The falling leaves.cpp")
                add_executable(Roads_in_the_north "Graph/Special graphs/10308/Roads in the north.cpp")
                add_executable(Family_tree "Graph/Special graphs/11615/Family tree.cpp")
