// This file generated using the Ned Batchelder's Cog inline 
// code generation tool. See http://nedbatchelder.com/code/cog/

#include <iostream>
// Add the testing header include.
/* [[[cog
   import cog
   cog.outl('#include "{0}.hpp"'.format(exec_name))
   ]]] */
#include "all_tests.hpp"
// [[[end]]]


int main(int argc, char* argv[])
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
std::cout << "Test test_evalfitness():" << std::endl;
test_failed = test_evalfitness();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_initrand():" << std::endl;
test_failed = test_initrand();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_rvarnormal():" << std::endl;
test_failed = test_rvarnormal();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_rvaruniform():" << std::endl;
test_failed = test_rvaruniform();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_seltruncation():" << std::endl;
test_failed = test_seltruncation();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
std::cout << "Test test_xokpoint():" << std::endl;
test_failed = test_xokpoint();
if(!test_failed) {
std::cout << " + Test succeeded." << std::endl;
} else {
std::cout << " + Test failed." << std::endl;
}
overall_failed |= test_failed;
// [[[end]]]

	return overall_failed;
}
