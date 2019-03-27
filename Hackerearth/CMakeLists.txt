cmake_minimum_required(VERSION 3.12)
project(Hackerearth)

find_package(Java REQUIRED)
include(UseJava)
set(CMAKE_CXX_STANDARD 17)

# Practice
    # Bit manipulation
    add_executable(Count_the_bits "Practice/Bit manipulation/Count the bits/Count the bits.cpp")
    add_executable(Jarvis_and_lone_integer "Practice/Bit manipulation/Jarvis and lone integer/Jarvis and lone integer.cpp")
    add_executable(Monk_and_the_box_of_cookies "Practice/Bit manipulation/Monk and the box of cookies/Monk and the box of cookies.cpp")
    add_executable(Sherlock_and_xor "Practice/Bit manipulation/Sherlock and XOR/Sherlock and XOR.cpp")
    add_executable(Subham_and_binary_strings "Practice/Bit manipulation/Subham and binary strings/Subham and binary strings.cpp")
    # Dynamic programming
    add_jar(Pseudo_equal_numbers "Practice/Dynamic programming/Pseudo-equal numbers/src/TestClass.java")

# Compete
    # Circuits
        # 2017
            # August
            add_executable(Gary_and_queries "Compete/Circuits/2017/August/Gary and queries/Gary and queries.cpp")
            add_executable(K_devices "Compete/Circuits/2017/August/K devices/K devices.cpp")
            # October
            add_executable(Card_game "Compete/Circuits/2017/October/Card game/Card game.cpp")
            add_executable(Polynomial_sign "Compete/Circuits/2017/October/Polynomial sign/Polynomial sign.cpp")
            # September
            add_executable(Bricks_and_building "Compete/Circuits/2017/September/Bricks and building/Bricks and building.cpp"
                    "Compete/Circuits/2017/September/Bricks and building/bin search.cpp")
            add_executable(Coin_game "Compete/Circuits/2017/September/Coin game/Coin game.cpp")
            add_executable(Little_shino_and_k_ancestors "Compete/Circuits/2017/September/Little shino and k ancestors/Little shino and k ancestors.cpp")
        # 2018
            # October
            add_executable(Question_paper "Compete/Circuits/2018/October/Quesion paper/Question paper.cpp")
            add_executable(Total_cost "Compete/Circuits/2018/October/Total cost/Total cost.cpp")
            add_executable(Reversing_elements "Compete/Circuits/2018/October/Reversing elements/Reversing elements.cpp")
        # 2019
            # March
            add_executable(Does_it_divide "Compete/Circuits/2019/March/Does it divide/Does it divide.cpp")