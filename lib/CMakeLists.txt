include_directories(${PROJECT_SOURCE_DIR}/inc)

add_library(
		cea
		SHARED
		opgenome.cpp
		opinitrand.cpp
		popgen.cpp
		prngisaac.cpp
		prnglcg.cpp
		rvaruniform.cpp
)
