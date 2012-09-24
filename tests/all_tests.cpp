// This file generated using Ned Batchelder's Cog inline 
// code generation tool. See http://nedbatchelder.com/code/cog/

#include <iostream>
// Add the testing header include.
/* [[[cog
   import cog
   cog.outl('#include "{0}.hpp"'.format(exec_name))
   ]]] */
#include "all_tests.hpp"
// [[[end]]]


int main()
{
	bool test_failed = false;
	bool overall_failed = false;

// Add call blocks for each test.
/* [[[cog
   import cog
   import os

   dir = os.listdir(os.path.dirname(cog.inFile))
   dir.sort()
   funcs = []
   for f in dir:
       if f.startswith('test_') and f.endswith('.cpp'):
           funcs.append(f.replace('.cpp', '()'))

   for func in funcs:
       cog.outl('std::cout << "Test {0}:" << std::endl;'.format(func))
       cog.outl('test_failed = {0};'.format(func))
       cog.outl('if(!test_failed) {')
       cog.outl('std::cout << " + Test succeeded." << std::endl;')
       cog.outl('} else {')
       cog.outl('std::cout << " + Test failed." << std::endl;')
       cog.outl('}')
       cog.outl('overall_failed |= test_failed;')
   ]]] */
std::cout << "Test test_init_rand():" << std::endl;
test_failed = test_init_rand();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_mut_offset():" << std::endl;
test_failed = test_mut_offset();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_point_spread():" << std::endl;
test_failed = test_point_spread();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_rvar_normal():" << std::endl;
test_failed = test_rvar_normal();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_rvar_uniform():" << std::endl;
test_failed = test_rvar_uniform();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_sel_trunc():" << std::endl;
test_failed = test_sel_trunc();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_term_fixed_time():" << std::endl;
test_failed = test_term_fixed_time();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_xo_npoint():" << std::endl;
test_failed = test_xo_npoint();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
// [[[end]]]

	return overall_failed;
}
