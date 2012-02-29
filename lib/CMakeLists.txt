include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(
	cea SHARED
	opgenome.cpp
	opinitrand.cpp
	opxokpoint.cpp
	popgen.cpp
	prngmlcgxorshift.cpp
	prngmwcxorshift.cpp
	prngkiss.cpp
	rvaruniform.cpp
)
