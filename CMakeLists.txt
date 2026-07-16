cmake_minimum_required(VERSION 3.14)

project(CompetitiveCoding)

# GoogleTest, fetched once here so any subproject can link GTest::gtest_main /
# GTest::gmock and register cases with gtest_discover_tests.
include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.15.2
)
# For Windows: prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_subdirectory(UVa)
add_subdirectory(Codeforces)
add_subdirectory(Codechef)
add_subdirectory(Hackerearth)
add_subdirectory(Hackerrank)
add_subdirectory(Leetcode)
add_subdirectory(Neetcode)
add_subdirectory(Techgig)
add_subdirectory(Topcoder)
add_subdirectory(SPOJ)
add_subdirectory(Educative.IO)