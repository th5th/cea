# Cmakelists.txt generated automatically from test files in /home/th5th/eng/cea/tests/ by /home/th5th/eng/cea/gentests.py.

include_directories(${PROJECT_SOURCE_DIR}/inc)
link_directories(${PROJECT_SOURCE_DIR}/bin)

add_executable(all_tests all_tests.cpp test_dummy.cpp)
set_target_properties(all_tests PROPERTIES COMPILE_FLAGS "--std=c++0x")
target_link_libraries(all_tests cea)
