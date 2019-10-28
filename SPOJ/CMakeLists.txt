cmake_minimum_required(VERSION 3.8)
project(SPOJ)

find_package(Java REQUIRED)
include(UseJava)

add_jar(FISHER "Practice/FISHER/src/Main.java")
