cmake_minimum_required(VERSION 3.5)

set(NAME "avm")

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Wextra")

project(${NAME})

add_executable(${NAME} src/main.cpp src/Action.cpp src/Action.hpp)