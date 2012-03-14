# libcea

### A Configurable Evolutionary Algorithms Library

Library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with a simple test generator written in Python. It is built in a CMake build system and version-controlled with git (obviously).

The final aim is a library which can be used to run "quick and dirty" EAs using the provided class specialisations, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent changes:

+ Several operators now in place - one of each kind with only OpTerm remaining to be represented.
+ Added evaluation operator which allows function pointers or `std::function` objects to be used as fitness functions.
