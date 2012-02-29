// All_tests.cpp generated automatically from test files in tests/ by ./gentests.py.

#include <iostream>
#include "all_tests.h"

int main(int argc, char* argv[])
{
	bool return_val = 0;
	return_val |= test_opxokpoint();
	std::cout << "Test test_opxokpoint(): ";
	if(!return_val)
		std::cout << "Test succeeded." << std::endl;
	else
		std::cout << "Test failed." << std::endl;

	return return_val;
}