libcea
======

Introduction
------------

Libcea is a library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with tools written in Python and Bash script. It is built in a CMake build system and version-controlled with git (obviously).

The final aim is a library which can be used to run "quick and dirty" EAs using the provided class specialisations, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent Changes
--------------

+ Began using try, catch and throw for error handling, and included tests of these in a few test cases.
+ Gradually thinking about maybe rewriting testgen.py so it doesn't end up as Python spaghetti, Python pretending to be C, or Python for Dummies. Must Try Harder.
+ Test cases in place for RVarNormal and RVarUniform based on the Kolmogorov-Smirnov test.

Todo List
---------

+ Cea/src/core/genome.hpp:         Add dependent [gs]etters for these fields to control state more closely.
+ Cea/src/ops/xokpoint.hpp: Allow variable number of children independent of parents.
+ Cea/src/ops/xokpoint.hpp: Possibly remove integer template parameters. Value?
+ Cea/src/ops/seltruncation.hpp: Investigation of manual optimisation vs. STL.
+ tests/test\_seltruncation.cpp: Move print\_pop into library - util/output.hpp?
