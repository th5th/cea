// All_tests.hpp generated automatically from test files in tests/ by gentests.py.
// Add the testing header guard.
/* [[[cog
   import cog
   import os
   cog.outl(''.join(['#ifndef ', exec_name.upper(), '_HPP']))
   cog.outl(''.join(['#define ', exec_name.upper(), '_HPP']))

   dir = os.listdir(os.path.dirname(cog.inFile))
   dir.sort()
   for f in dir:
       if f.startswith('test_') and f.endswith('.cpp'):
           cog.outl(''.join(['bool ', f.replace('.cpp', '();')]))

   cog.outl(''.join(['#endif // ', exec_name.upper(), '_HPP']))

   ]]] */
#ifndef ALL_TESTS_HPP
#define ALL_TESTS_HPP
bool test_evalfitness();
bool test_initrand();
bool test_rvarnormal();
bool test_rvaruniform();
bool test_seltruncation();
bool test_xokpoint();
#endif // ALL_TESTS_HPP
// [[[end]]]
