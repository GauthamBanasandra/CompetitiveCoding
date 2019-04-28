cmake_minimum_required(VERSION 3.8)
project(Google_code_jam)

set(CMAKE_CXX_STANDARD 17)

add_executable(Saving_the_universe "2008/Qualification round/Saving the universe/Saving the universe.cpp")
add_executable(Train_timetable "2008/Qualification round/Train timetable/Train timetable.cpp" "2008/Qualification round/Train timetable/utils.cpp")
add_executable(Minimum_scalar_product "2008/Round 1A/Minimum scalar product/Minimum scalar product.cpp")

add_executable(Trouble_sort "2018/Qualification round/Trouble sort/Trouble sort.cpp" "2018/Qualification round/Trouble sort/utils.cpp")
add_executable(Saving_the_universe_again "2018/Qualification round/Saving the universe again/Saving the universe again.cpp")

add_executable(Waffle_choppers "2018/Round 1A/Waffle choppers/Waffle choppers.cpp")

# 2019
    # Qualification round
    add_executable(Foregone_solution "2019/Qualification round/Foregone solution/Foregone solution.cpp")
    add_executable(You_can_go_your_own_way "2019/Qualification round/You can go your own way/You can go your own way.cpp")
    # Round 1A
    add_executable(Pylons "2019/Round 1A/Pylons/Pylons.cpp")
    add_executable(Alien_rhyme "2019/Round 1A/Alien rhyme/Alien rhyme.cpp")
    # Round 1B
    add_executable(Manhattan_crepe_cart "2019/Round 1B/Manhattan crepe cart/Manhattan crepe cart.cpp")