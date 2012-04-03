libcea
======

Introduction
------------

Libcea is a library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with a few tool scripts written in Bash script. It is built with the CMake build system and version-controlled with git (obviously). [Cog][coglink] is used to generate test code from Python embedded in C++ source.

[coglink]: http://nedbatchelder.com/code/cog/

The final aim is a library which can be used to run "quick and dirty" EAs using the provided class templates, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent Changes
--------------

+ Rolled back allocator changes. Will implement later perhaps...
+ After some fiddling, the `make` and `make_push_back` member functions of `alg` have (probably) been superseded by the `obj_fact` class and its `get<ObjClass>` member function. This allows users to produce compatible `alg` and `op_*` objects easily, without breaking encapsulation.
+ Tests largely redone. Some are only demo cases at the moment, with no value checking undertaken.
+ Major redesign to allow populations to be built from _any_ roughly STL compliant containers. Users will write `cea::cea<std::vector, std::list, float> myCeaAlg(num_individuals, num_genes);`, for example.

Todo List
---------

+ Cea/src/ops/xo\_npoint.hpp: Allow variable number of children independent of parents.
+ Cea/src/ops/xo\_npoint.hpp: Handle parents.size() + children.size() != p.size().
+ Cea/src/ops/xo\_npoint.hpp: Allow list-like genomes to take advantage of their structure by using splce-like operations here.
+ Cea/src/ops/sel\_trunc.hpp: Make op\_sel\_trunc work properly with non-RA iterators.
+ Cea/src/ops/sel\_trunc.hpp: Implementation reorders the population - desirable? 
