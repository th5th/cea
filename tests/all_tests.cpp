// All_tests.cpp generated automatically from test files in tests/ by ./gentests.py.

#include <iostream>
#include "all_tests.h"

int main(int argc, char* argv[])
{
	bool return_val = 1;
	return_val = test_rvu();
	std::cout << "Test test_rvu(): ";
	if(!return_val)
		std::cout << "Test succeeded." << std::endl;
	else
		std::cout << "Test failed." << std::endl;

	return return_val;
}