#include <iostream>

#include <cea.h>
#include <cea-operators.h>
#include <cea-rand.h>

using namespace cea;

bool test_rvu()
{
	Pop<double> my_pop(10, 3);

	PrngISAAC prng;
	RVarUniform rv(7, &prng);
	OpInitRand<double> my_rand(&rv);

	my_rand.apply_to(my_pop);

	std::vector< Genome<double> >::iterator it_gno;
	std::list<double>::iterator it_genes;
	for(it_gno = my_pop.begin(); it_gno != my_pop.end(); ++it_gno)
	{
		for(it_genes = it_gno->begin(); it_genes != it_gno->end(); ++it_genes)
			std::cout << *it_genes << " ";
		std::cout << std::endl;
	}

	return 0;
}
