cmake_minimum_required(VERSION 2.6)
project(cea)

set(cea_VERSION_MAJOR 0)
set(cea_VERSION_MINOR 1)

add_subdirectory(lib bin)
add_subdirectory(tests bin)
