// All_tests.cpp generated automatically from test files in tests/ by ./gentests.py.

#include <iostream>
#include "all_tests.h"

int main(int argc, char* argv[])
{
	bool return_val = 1;
	std::cout << "Test test_rvu(): ";
	if(!(return_val = test_rvu()))
		std::cout << "succeeded." << std::endl;
	else
		std::cout << "failed." << std::endl;

	return return_val;
}