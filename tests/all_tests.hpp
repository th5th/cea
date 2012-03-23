// This file generated using the Ned Batchelder's Cog inline 
// code generation tool. See http://nedbatchelder.com/code/cog/

/* [[[cog
   import cog
   import os
   cog.outl('#ifndef {0}_HPP'.format(exec_name.upper()))
   cog.outl('#define {0}_HPP'.format(exec_name.upper()))

   dir = os.listdir(os.path.dirname(cog.inFile))
   dir.sort()
   for f in dir:
       if f.startswith('test_') and f.endswith('.cpp'):
           cog.outl('bool {0}'.format(f.replace('.cpp', '();')))

   cog.outl('#endif // {0}_HPP'.format(exec_name.upper()))

   ]]] */
#ifndef ALL_TESTS_HPP
#define ALL_TESTS_HPP
bool test_core();
#endif // ALL_TESTS_HPP
// [[[end]]]
