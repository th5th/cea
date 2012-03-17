// All_tests.cpp generated automatically from test files in tests/ by gentests.py.

#include <iostream>
#include "all_tests.hpp"

int main(int argc, char* argv[])
{
	bool test_failed = false;
	bool overall_failed = false;

	std::cout << "Test test_rvaruniform():" << std::endl;
	test_failed = test_rvaruniform();
	if(!test_failed)
		std::cout << " + Test succeeded." << std::endl;
	else
		std::cout << " + Test failed." << std::endl;

	overall_failed |= test_failed;

	std::cout << "Test test_seltruncation():" << std::endl;
	test_failed = test_seltruncation();
	if(!test_failed)
		std::cout << " + Test succeeded." << std::endl;
	else
		std::cout << " + Test failed." << std::endl;

	overall_failed |= test_failed;

	std::cout << "Test test_evalfitness():" << std::endl;
	test_failed = test_evalfitness();
	if(!test_failed)
		std::cout << " + Test succeeded." << std::endl;
	else
		std::cout << " + Test failed." << std::endl;

	overall_failed |= test_failed;

	std::cout << "Test test_initrand():" << std::endl;
	test_failed = test_initrand();
	if(!test_failed)
		std::cout << " + Test succeeded." << std::endl;
	else
		std::cout << " + Test failed." << std::endl;

	overall_failed |= test_failed;

	std::cout << "Test test_xokpoint():" << std::endl;
	test_failed = test_xokpoint();
	if(!test_failed)
		std::cout << " + Test succeeded." << std::endl;
	else
		std::cout << " + Test failed." << std::endl;

	overall_failed |= test_failed;

	std::cout << "Test test_rvarnormal():" << std::endl;
	test_failed = test_rvarnormal();
	if(!test_failed)
		std::cout << " + Test succeeded." << std::endl;
	else
		std::cout << " + Test failed." << std::endl;

	overall_failed |= test_failed;

	return overall_failed;
}