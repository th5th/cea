// K-point crossover operator.
/*
   + Find two available genomes in the population.
   + Select two parent genomes in the population.
   + Generate K random points in the range (0,genome.size()).
   + Determine which genome is the majority parent.
   + Conduct K+1 block copies from the parents to the children
     from alternating parents such that the majority parent
     passes on the majority of it's genome.

     K = 4 swap points

     Majority parent:
     [    |########|     |#########|   ] (17 genes passed on)

     Minority parent:
     [####|        |#####|         |###] (12 genes passed on)
*/
#include <algorithm>
#include <iostream>

#include <cea-operators.h>

namespace cea
{
	template <typename T>
	OpXoKpoint<T>::OpXoKpoint(RVar<uint64_t> * src)
	{
		source = src;
		xop = 4;	// Number of crossover points.
		par = 2;	// Number of parents (and thus children).
		fitter_maj= false;
	}

	template <typename T>
	void OpXoKpoint<T>::apply_to(Pop<T>& p)
	{
		std::vector< Genome<T>* > pa;
		std::vector< Genome<T>* > ch;

		typename std::vector< Genome<T> >::iterator g_it = p.begin();
		int s = g_it->size();
		for(; g_it < p.end(); ++g_it)
		{

			// Find 2 unavailable and 2 available genomes.
			if(g_it->is_avail() == true)
			{
				ch.push_back(&*g_it);
			}
			else
			{
				pa.push_back(&*g_it);
			}

			// If we have enough in pa and ch, do crossover.
			if(ch.size() >= par && pa.size() >= par)
			{
				// Generate some crossover points.
				std::vector<uint64_t> xops(xop+2, 0);

				for(uint32_t i = 1; i < xop+1; ++i)
				{
					xops[i] = source->rand() % s;
				}

				xops[xop+1] = s;
				std::sort(xops.begin(), xops.end());

				if(fitter_maj == true)
				{
					// Re-order parents so fittest contributes most to children.
					std::vector<uint64_t> contribs;
					contribs.reserve(par);
					for(uint32_t i = 0; i < par; ++i)
					{
						uint64_t c = 0;
						for(uint32_t j = i+1; j < xops.size(); j += par)
						{
							c += (xops[j] - xops[j-1]);
						}
						contribs[i] = c;
					}
					// Re-order pa according to contribs.
					// ...
				}

				// Copy pa into ch[0] using crossover points from above.
				for(uint32_t i = 0; i < par; ++i)
				{
					for(uint32_t j = i+1; j < xops.size(); j += par)
					{
						std::copy(pa[i]->begin() + xops[j-1], pa[i]->begin() + xops[j], ch[0]->begin() + xops[j-1]);
					}
				}

				// Polish ch[0]'s members (lol) and copy to ch[i].
				ch[0]->set_avail(false); ch[0]->set_fitness(-1);
				for(uint32_t i = 1; i < par; ++i)
				{
					*ch[i] = *ch[0];
				}

				// Empty parent and child buffers for next iteration.
				pa.clear(); ch.clear();
			}
		}

		// Check for leftovers!
		if(pa.size() != 0 || ch.size() != 0)
		{
			// Do something.
		}
	}

	template class OpXoKpoint<uint64_t>;
	template class OpXoKpoint<double>;
}
