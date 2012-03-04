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
	}

	template <typename T>
	void OpXoKpoint<T>::check_points(std::vector<uint64_t>& points, uint64_t s)
	{
		// How big points is supposed to be.
		uint64_t final_size = points.size();

		// Sort and cull repeated els.
		std::sort(points.begin(), points.end());
		points.resize(std::unique(points.begin(), points.end()) - points.begin());

		if(points.size() == final_size)
		{
			for(uint64_t i = 0; i < points.size(); ++i)
			{
				std::cout << points[i] << " ";
			}
			std::cout << std::endl;
			return;
		}

		// Top up points.
		while(points.size() < final_size)
		{
			points.push_back(source->rand() % s);
		}

		// Recurse to make sure what we've added is ok.
		check_points(points, s);
	}

	template <typename T>
	void OpXoKpoint<T>::gen_points(std::vector<uint64_t>& points, uint64_t s)
	{
		// Generate some crossover points.
		if(points.size() != 0)
		{
			points.clear();
		}
		points.resize(xop+2, 0);

		for(uint32_t i = 1; i < xop+1; ++i)
		{
			points[i] = source->rand() % s;
		}

		points[xop+1] = s;

		// Remove duplicates and top up.
		check_points(points, s);

		return;
	}

	template <typename T>
	void OpXoKpoint<T>::do_xo(std::vector<uint64_t> points, std::deque< Genome<T>* >& p, std::deque< Genome<T>* >& c)
	{
		// Copy over genes according to vector points.
		for(uint32_t i = 0; i < par; ++i)
		{
			for(uint32_t j = i+1; j < points.size(); j += par)
			{
				std::copy(p[0]->begin() + points[j-1], p[0]->begin() + points[j], c[0]->begin() + points[j-1]);
			}
			p.pop_front();
		}

		// Polish c[0]'s members (lol) and copy to c[1].
		c[0]->set_avail(false); c[0]->set_fitness(-1);
		for(uint32_t i = 1; i < par; ++i)
		{
			*c[1] = *c[0];
			c.pop_front();
		}

		// Pop last child pointer - doesn't need to copied on.
		c.pop_front();

		return;
	}

	template <typename T>
	void OpXoKpoint<T>::apply_to(Pop<T>& p)
	{
		std::vector<uint64_t> xo_points;
		std::deque< Genome<T>* > pa;
		std::deque< Genome<T>* > ch;

		typename std::vector< Genome<T> >::iterator g_it = p.begin();
		uint64_t s = g_it->size();
		for(; g_it < p.end(); ++g_it)
		{
			// Separate unavailable and available genomes.
			if(g_it->is_avail() == true)
			{
				ch.push_back(&*g_it);
			}
			else
			{
				pa.push_back(&*g_it);
			}
		}

		while(ch.size() >= par && pa.size() >= par)
		{
			// Generate unique crossover points and go.
			gen_points(xo_points, s);
			do_xo(xo_points, pa, ch);
		}

		// Check for leftovers!
		if(pa.size() != 0 || ch.size() != 0)
		{
			// Do something.
			std::cout << "Population size not compatible with this operator's settings!" << std::endl;
		}
	}

	template class OpXoKpoint<uint64_t>;
	template class OpXoKpoint<double>;
}
