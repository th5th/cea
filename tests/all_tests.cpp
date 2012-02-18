// All_tests.cpp generated automatically from test files in /home/th5th/eng/cea/tests/ by /home/th5th/eng/cea/gentests.py.

#include <iostream>
#include "all_tests.h"

int main(int argc, char* argv[])
{
	bool return_val = 1;
	std::cout << "Test test_dummy(): ";
	if(!(return_val = test_dummy()))
		std::cout << "succeeded." << std::endl;
	else
		std::cout << "failed." << std::endl;

	return return_val;
}