cmake_minimum_required(VERSION 3.31)
project(LindenShoreOA)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(LindenShoreOA main.cpp pnl_calculator.cpp)
