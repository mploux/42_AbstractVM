cmake_minimum_required(VERSION 3.5.1)

set(NAME "avm")

project(${NAME})

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

add_executable(${NAME} src/main.cpp src/Action.cpp src/Action.hpp)
