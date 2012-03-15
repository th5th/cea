# Cmakelists.txt generated automatically from test files in tests/ by gentests.py.

include_directories(${PROJECT_SOURCE_DIR})

add_executable(all_tests all_tests.cpp test_seltruncation.cpp test_evalfitness.cpp test_initrand.cpp test_xokpoint.cpp test_rvarnormal.cpp)
