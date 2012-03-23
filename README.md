libcea
======

Introduction
------------

Libcea is a library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with a few tool scripts written in Bash script. It is built with the CMake build system and version-controlled with git (obviously).

The final aim is a library which can be used to run "quick and dirty" EAs using the provided class templates, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent Changes
--------------

+ Fleshed out main cea class, including `make\_op` member, which instantiates templated classes (which provide the correct parameters) for use as genetic operators compatible with the calling cea instance.
+ Major redesign to allow populations to be built from _any_ roughly STL compliant containers. Users will write `cea::cea<std::vector, std::list, float> myCeaAlg(num_individuals, num_genes);`, for example.
+ gentests.py discarded in favour of [Cog][coglink], a third party tool allowing Python to be embedded in C++ (or any) files for code generation.
+ Began using try, catch and throw for error handling, and included tests of these in a few test cases.

[coglink]: http://nedbatchelder.com/code/cog/

Todo List
---------

+ Cea/src/ops/xokpoint.hpp: Allow variable number of children independent of parents.
+ Cea/src/ops/xokpoint.hpp: Possibly remove integer template parameters. Value?
+ Cea/src/ops/seltruncation.hpp: Investigation of manual optimisation vs. STL.
+ tests/test\_seltruncation.cpp: Move print\_pop into library - util/output.hpp?
