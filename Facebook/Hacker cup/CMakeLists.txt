cmake_minimum_required(VERSION 3.10)
project(Hacker_cup)

set(CMAKE_CXX_STANDARD 11)

# 2018
	# Qualification round
	add_executable(Tourist "2018/Qualification round/Tourist/Tourist.cpp" utils/print.cpp)
	# Round 1
	add_executable(Let_it_flow "2018/Round 1/Let it flow/Let it flow.cpp")

# 2020
	# Qualification round
	add_executable(Travel_restrictions "2020/Qualification round/Travel restrictions/Travel restrictions.cpp")
