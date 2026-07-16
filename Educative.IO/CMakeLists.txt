cmake_minimum_required(VERSION 3.14)
project(Educative_IO)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GoogleTest (GTest::gtest_main, gtest_discover_tests) is provided by the
# top-level CompetitiveCoding CMakeLists.

# Patterns
	# Two pointers
	add_executable(Remove_nth_Node_from_End_of_List
		"Patterns/Two Pointers/Remove nth Node from End of List/Remove nth Node from End of List.cpp"
		"Patterns/Two Pointers/Remove nth Node from End of List/ListNode.cpp"
	"Patterns/Two Pointers/Remove nth Node from End of List/main.cpp")
	target_link_libraries(Remove_nth_Node_from_End_of_List PRIVATE GTest::gtest_main)
	gtest_discover_tests(Remove_nth_Node_from_End_of_List)
	