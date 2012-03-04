#include <iostream>
#include <iomanip>

#include <cea.h>
#include <cea-operators.h>
#include <cea-rand.h>

using namespace cea;

bool test_opxokpoint()
{
	// Make a population, then apply the XoKpoint operator.
	Pop<uint64_t> p(8,37);
	p.begin()->set_avail(false);
	(p.begin()+1)->set_avail(false);
	(p.begin()+4)->set_avail(false);
	(p.begin()+5)->set_avail(false);

	DebugRVar<uint64_t> debug1;
	debug1.set(0, 1);
	OpInitRand<uint64_t> vals(&debug1);
	vals.apply_to(p);

	PrngMLCGXORShift derp(194571);
	RVarUniform<uint64_t> debug2(&derp, 0, 37);;
	
	OpXoKpoint<uint64_t> xo(&debug2);
	xo.set_xop(3);
	xo.set_par(2);
	xo.apply_to(p);

	// Check state of p...
	bool r_val = 1;

	std::vector< Genome<uint64_t> >::iterator it_gno;
	std::vector<uint64_t>::iterator it_genes;
	for(it_gno = p.begin(); it_gno != p.end(); ++it_gno)
	{
		for(it_genes = it_gno->begin(); it_genes != it_gno->end(); ++it_genes)
			std::cout << std::setw(4) << std::right << *it_genes;
		std::cout << std::endl;
	}

	return 1;
}
