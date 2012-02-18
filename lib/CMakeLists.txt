include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(cea SHARED prngisaac.cpp prnglcg.cpp)
set_target_properties(cea PROPERTIES COMPILE_FLAGS "--std=c++0x")
