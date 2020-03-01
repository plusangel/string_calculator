cmake_minimum_required(VERSION 3.15)
project(string_calculator)

set(CMAKE_CXX_STANDARD 17)

add_library(simple_calculator simple_calc.cpp)

add_executable(calc_tests simple_calc_tests.cpp)
target_link_libraries(calc_tests simple_calculator)