cmake_minimum_required(VERSION 3.8)
project(kickstart)
set(CMAKE_CXX_STANDARD 17)
find_package(Java REQUIRED)
include(UseJava)

# 2018
    # Practice
    add_executable(GBus_count "2018/Practice round/GBus count/GBus count.cpp")
    add_executable(Sort_a_scrambled_itinerary "2018/Practice round/Sort a scrambled itinerary/Sort a scrambled itinerary.cpp")
    add_executable(Sums_of_sums "2018/Practice round/Sums of sums/Sums of sums.cpp")
    add_executable(Googol_string "2018/Practice round/Googol string/Googol string.cpp")
    # A
    add_jar(Even_digits "2018/A/A/Even digits/src/Calculator.java"
            "2018/A/A/Even digits/src/EvenDigits.java"
            "2018/A/A/Even digits/src/EvenDigitsArray.java")
    # B
    add_executable(No_nine "2018/B/A/No nine.cpp")
    # F
    add_executable(Common_anagrams "2018/F/A/Common anagrams.cpp")
    # H
    add_executable(Big_buttons "2018/H/A/Big buttons.cpp")
    add_executable(Mural "2018/H/B/Mural.cpp")
# 2019
        # Round A
        add_executable(Training "2019/Round A/A/Training.cpp")
        # Round E
        add_executable(Cherries_mesh "2019/Round A/E/Cherries mesh.cpp")