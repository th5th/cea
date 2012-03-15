libcea
======

Introduction
------------

Libcea is a library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with tools written in Python and Bash script. It is built in a CMake build system and version-controlled with git (obviously).

The final aim is a library which can be used to run "quick and dirty" EAs using the provided class specialisations, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent Changes
--------------

+ Several operators now in place - one of each kind with only OpTerm remaining to be represented.
+ Added evaluation operator which allows function pointers or `std::function` objects to be used as fitness functions.
+ Added todo.sh - a simple todo list maker in Bash script. It made the list below!

Todo List
---------

+ Cea/src/ops/xokpoint.hpp: Allow variable number of children independent of parents.
+ Cea/src/ops/xokpoint.hpp: Possibly remove integer template parameters. Value?
+ Cea/src/ops/seltruncation.hpp: Investigation of manual optimisation vs. STL.
+ Cea/src/ops/seltruncation.hpp: Convert throws to OO.
+ tests/test\_seltruncation.cpp: Move print\_pop into library - util/output.hpp?
