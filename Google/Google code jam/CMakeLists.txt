cmake_minimum_required(VERSION 3.8)
project(Google_code_jam)

set(CMAKE_CXX_STANDARD 11)

add_executable(Saving_the_universe "2008/Qualification round/Saving the universe/Saving the universe.cpp")
add_executable(Train_timetable "2008/Qualification round/Train timetable/Train timetable.cpp" "2008/Qualification round/Train timetable/utils.cpp")
add_executable(Minimum_scalar_product "2008/Round 1A/Minimum scalar product/Minimum scalar product.cpp")

add_executable(Trouble_sort "2018/Qualification round/Trouble sort/Trouble sort.cpp" "2018/Qualification round/Trouble sort/utils.cpp")
add_executable(Saving_the_universe_again "2018/Qualification round/Saving the universe again/Saving the universe again.cpp")

add_executable(Waffle_choppers "2018/Round 1A/Waffle choppers/Waffle choppers.cpp")