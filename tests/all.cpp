// All.cpp generated automatically from test files in tests/ by gentests.py.

#include <iostream>
#include "all.hpp"

int main(int argc, char* argv[])
{
	bool test_failed = false;
	bool overall_failed = false;

	test_failed = test_initrand();

	std::cout << "Test test_initrand(): ";
	if(!test_failed)
		std::cout << "Test succeeded." << std::endl;
	else
		std::cout << "Test failed." << std::endl;

	overall_failed |= test_failed;

	test_failed = test_xokpoint();

	std::cout << "Test test_xokpoint(): ";
	if(!test_failed)
		std::cout << "Test succeeded." << std::endl;
	else
		std::cout << "Test failed." << std::endl;

	overall_failed |= test_failed;

	return overall_failed;
}