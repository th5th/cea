cmake_minimum_required(VERSION 2.6)
project(cea)

set(CMAKE_CXX_FLAGS "-DCEA_DEBUG -g --std=c++0x -Wall -Wextra")

add_subdirectory(tests)

# Use Cog to ensure test source is up to date.
add_custom_target(cog ALL cog.py -U -r -D exec_name=all_tests @coglist)
