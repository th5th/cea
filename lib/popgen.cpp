// Implementation of Genome and Pop data structures.
#include <cea.h>

namespace cea
{
	template <typename T>
	Genome<T>::Genome()
	{
		set_fitness(0.0);
		set_avail(true);
	}

	template <typename T>
	Genome<T>::Genome(int size)
	{
		set_fitness(0.0);
		set_avail(true);
		genes.resize(size);
	}

	template class Genome<uint64_t>;
	template class Genome<double>;

	template <typename T>
	Pop<T>::Pop(int p_s, int g_s)
	{
		pop.resize(p_s);
		typename std::vector< Genome<T> >::iterator it;
		for(it = pop.begin(); it != pop.end(); ++it)
			it->resize(g_s);
	}

	template class Pop<uint64_t>;
	template class Pop<double>;
}
