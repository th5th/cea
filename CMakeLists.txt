cmake_minimum_required(VERSION 2.6)
project(cea)

set(cea_VERSION_MAJOR 0)
set(cea_VERSION_MINOR 1)

set(CMAKE_CXX_FLAGS "-DCEA_DEBUG -g --std=c++0x -Wall -Wextra")

add_subdirectory(tests)
