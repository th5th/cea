libcea
======

Introduction
------------

Libcea is a library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with a few tool scripts written in Bash script. It is built with the CMake build system and version-controlled with git (obviously).

The final aim is a library which can be used to run "quick and dirty" EAs using the provided class templates, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent Changes
--------------

+ Tests largely redone. Some are only demo cases at the moment, with no value checking undertaken.
+ Operators reimplemented as functors compatible with alg's `make_op` member.
+ Fleshed out main cea class, including `make_op` member, which instantiates templated classes (which provide the correct parameters) for use as genetic operators compatible with the calling cea instance.
+ Major redesign to allow populations to be built from _any_ roughly STL compliant containers. Users will write `cea::cea<std::vector, std::list, float> myCeaAlg(num_individuals, num_genes);`, for example.
+ gentests.py discarded in favour of [Cog][coglink], a third party tool allowing Python to be embedded in C++ (or any) files for code generation.

[coglink]: http://nedbatchelder.com/code/cog/

Todo List
---------

+ Cea/src/ops/xo\_npoint.hpp: Allow variable number of children independent of parents.
+ Cea/src/ops/xo\_npoint.hpp: Handle parents.size() + children.size() != p.size().
+ Cea/src/ops/xo\_npoint.hpp: Allow list-like genomes to take advantage of their structure by using splce-like operations here.
+ Cea/src/ops/sel\_trunc.hpp: Make op\_sel\_trunc work properly with non-RA iterators.
+ Cea/src/ops/sel\_trunc.hpp: Implementation reorders the population - desirable? 
