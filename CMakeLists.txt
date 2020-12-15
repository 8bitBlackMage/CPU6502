cmake_minimum_required(VERSION 3.17)
project(6502)

set(CMAKE_CXX_STANDARD 14)

add_executable(6502 main.cpp cpu6502.cpp cpu6502.h RAM.cpp RAM.h)