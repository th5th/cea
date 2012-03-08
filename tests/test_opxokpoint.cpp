#include <iostream>
#include <iomanip>

#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_opxokpoint()
{
	// Make a population, then apply the XoKpoint operator.
	Pop<float> p(8,24);
	p.begin()->set_avail(false);
	(p.begin()+1)->set_avail(false);
	(p.begin()+4)->set_avail(false);
	(p.begin()+5)->set_avail(false);

    PrngKISS p1;
	RVarUniform<float> r(&p1, -3.0, 3.0);
	OpInitRand<float> vals(&r);
	vals.apply_to(p);

    RVarUniform<uint64_t> r_int(&p1, 0, 24);
	OpXoKpoint<float, 2, 3> xo(&r_int);
	xo.apply_to(p);

	// Check state of p...
	std::vector< Genome<float> >::iterator it_gno;
	std::vector<float>::iterator it_genes;
	for(it_gno = p.begin(); it_gno != p.end(); ++it_gno)
	{
		for(it_genes = it_gno->begin(); it_genes != it_gno->end(); ++it_genes)
			std::cout << std::setprecision(3) << std::setw(6) << std::right << *it_genes;
		std::cout << std::endl;
	}
	return 1;
}
