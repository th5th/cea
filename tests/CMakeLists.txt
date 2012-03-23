# Cmakelists.txt generated using the Ned Batchelder's Cog inline 
# code generation tool. See http://nedbatchelder.com/code/cog/

include_directories(${PROJECT_SOURCE_DIR})

# This Cog section inserts the add_executable(...),
# add_library(...) and target_link_libraries(...) directives.
# It also uses add_dependencies to make the exec_name target
# depend on the cog target.
# [[[cog
#   import cog
#   import os
#
#   cog.outl('add_executable(')
#   cog.outl(exec_name)
#   cog.outl('{0}.cpp'.format(exec_name))
#
#   dir = os.path.dirname(cog.inFile)
#   for f in os.listdir(dir):
#       if f.startswith('test_') and f.endswith('.cpp'):
#           cog.outl(f)
#
#   cog.outl(')')
#   cog.outl('add_dependencies({0} cog)'.format(exec_name))
#
#   static_libs = ['kstest']
#   for lib in static_libs:
#       cog.outl('add_library({0} STATIC {0}.cpp)'.format(lib))
#
#   cog.outl('target_link_libraries(')
#   cog.outl(exec_name)
#   for lib in static_libs:
#       cog.outl(lib)
#   cog.outl(')')
# ]]]
add_executable(
all_tests
all_tests.cpp
test_core.cpp
)
#add_dependencies(all_tests cog)
#add_library(kstest STATIC kstest.cpp)
#target_link_libraries(
#all_tests
#kstest
#)
# [[[end]]]
