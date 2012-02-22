#include <iostream>

#include <cea.h>
#include <cea-operators.h>
#include <cea-rand.h>

using namespace cea;

bool test_rvu()
{
	//Pop<uint64_t> my_pop(10, 3);

	PrngKISS prng;
	/*
	RVarUniform<uint64_t> rv(&prng, 0, 1000);
	OpInitRand<uint64_t> my_rand(&rv);

	my_rand.apply_to(my_pop);

	std::vector< Genome<uint64_t> >::iterator it_gno;
	std::list<uint64_t>::iterator it_genes;
	for(it_gno = my_pop.begin(); it_gno != my_pop.end(); ++it_gno)
	{
		for(it_genes = it_gno->begin(); it_genes != it_gno->end(); ++it_genes)
			std::cout << *it_genes << " ";
		std::cout << std::endl;
	}
	*/
	for(int i = 0; i < 1e9; ++i)
		prng.rand();

	return 0;
}
