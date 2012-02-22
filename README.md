# libcea

### A Configurable Evolutionary Algorithms Library

Library for running evolutionary algorithms. Currently under heavy development, libcea is being written in C++ with a simple test generator written in Python. It is built in a CMake build system and version-controlled with git (obviously).

The final aim is a library which can be used to run "quick and dirty" EAs using the built in class specialisations, or heavily, if not completely, customised algorithms which merely take advantage of the framework and so-called "meta-algorithm" which CEA provides.

Recent changes:
+ High quality, high speed PRNGs written based on work of Geroge Marsaglia and the principle of combination. In a rough benchmark I achieved generation rates of 26m (highest quality, period) to 45m (lowest quality, period) 64-bit integers generated per second. I have an old 3Ghz Athlon 6000.
