cmake_minimum_required(VERSION 3.14)
project(R-Tree)

set(CMAKE_CXX_STANDARD 17)

add_executable(R-Tree rtree.cpp rtree.h main.cpp)