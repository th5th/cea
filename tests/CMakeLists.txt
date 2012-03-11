# Cmakelists.txt generated automatically from test files in tests/ by gentests.py.

include_directories(${PROJECT_SOURCE_DIR})

add_executable(all all.cpp test_initrand.cpp test_opevalfitness.cpp test_xokpoint.cpp test_rvarnormal.cpp)
