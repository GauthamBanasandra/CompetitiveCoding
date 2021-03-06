cmake_minimum_required(VERSION 3.12)
project(Codechef)

set(CMAKE_CXX_STANDARD 17)
find_package(Java REQUIRED)
include(UseJava)

# Compete
    # 2018 October challenge
    add_executable(Chef_and_serves "Compete/2018/October challenge/Division 2/CHSERVE/Chef and serves.cpp")
    add_executable(Byte_to_bit "Compete/2018/October challenge/Division 2/BITOBYT/Byte to bit.cpp")
    # 2018 November challenge
    add_executable(Chef_and_difficult_contests "Compete/2018/November challenge/CHFTIRED/Chef and difficult contests.cpp")
    add_executable(Chef_and_happiness "Compete/2018/November challenge/CHHAPPY/Chef and happiness.cpp")
    add_executable(Chef_and_ridges "Compete/2018/November challenge/PRDRG/Chef and ridges.cpp")
    add_executable(Appy_loves_one "Compete/2018/November challenge/HMAPPY1/Appy loves one.cpp")
    add_executable(Magician_versus_chef_2 "Compete/2018/November challenge/MAGICHF2/Magician versus chef 2.cpp")
    add_executable(Good_median "Compete/2018/November challenge/GMEDIAN/Good median.cpp")
    add_executable(Chef_primes_and_trees "Compete/2018/November challenge/PRITREE/Chef primes and trees.cpp")
    # 2018 November cook off
    add_executable(Truth_and_dare "Compete/2018/November cook off/TRUEDARE/Truth and dare.cpp")
    add_executable(Beautiful_garland "Compete/2018/November cook off/BEAUTGAR/Beautiful garland.cpp")
    # 2018 November lunchtime
    add_executable(Event "Compete/2018/November lunchtime/EVENT/Event.cpp")
    # 2018 December challenge
    add_executable(Chef_and_interactive_contests "Compete/2018/December challenge/CHFINTRO/Chef and interactive contests.cpp")
    add_executable(Chef_and_an_ideal_problem "Compete/2018/December challenge/CHFIDEAL/Chef and an ideal problem.cpp")
    add_executable(Max_and_electrical_panel "Compete/2018/December challenge/MAXEP/Max and electrical panel.cpp")
    # 2019 April challenge
    add_executable(Maximum_remaining "Compete/2019/April challenge/MAXREM/Maximum remaining.cpp")
    add_executable(Fence "Compete/2019/April challenge/FENCE/Fencing.cpp")
    add_executable(Subtree_removal "Compete/2019/April challenge/SUBREM/Subtree removal.cpp")
    add_executable(Friend_or_girlfriend "Compete/2019/April challenge/STRCH/Friend or girlfriend.cpp")
    # 2019 April cook-off
    add_executable(Making_a_meal "Compete/2019/April cook-off/CFMM/Making a meal.cpp")
    add_executable(Chef_learning_hungarian_algorithm "Compete/2019/April cook-off/HUNGALGO/Chef learning hungarian algorithm.cpp")
    add_executable(Pied_piper_vs_hooli "Compete/2019/April cook-off/PEWDSVTS/Pied piper vs hooli.cpp")
    # 2019 April lunchtime
    add_executable(Attendance "Compete/2019/April lunchtime/ATTND/Attendance.cpp")
    add_executable(Fast_food "Compete/2019/April lunchtime/FASTFOOD/Fast food.cpp")
    add_executable(Minimum_sum "Compete/2019/April lunchtime/MINARRS/Minimum sum.cpp")
    add_executable(Chef_rami_and_inventions "Compete/2019/April lunchtime/CHEFRAMI/Chef rami and inventions.cpp")
    # 2019 May cook-off
    add_executable(Chain_reaction "Compete/2019/May cook-off/REACTION/Chain reaction.cpp")
    add_executable(Misha_and_nice_sets "Compete/2019/May cook-off/GCDSET/Misha and nice sets.cpp")
# Practice
add_executable(Closing_the_tweets "Practice/Medium/TWTCLOSE/Closing the tweets.cpp")
add_executable(The_next_palindrome "Practice/Medium/PALIN/The next palindrome.cpp")