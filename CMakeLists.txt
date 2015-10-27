cmake_minimum_required(VERSION 3.3)
project(ABBThread)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++11")

set(SOURCE_FILES main.cpp ABB.h Node.h random_numbers.h Time.h)
add_executable(ABBThread ${SOURCE_FILES})