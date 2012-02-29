// Random initialisation operator.
#include <cea-operators.h>

namespace cea
{
	template <typename T>
	void OpInitRand<T>::apply_tog(Genome<T>& g)
	{
		typename std::vector<T>::iterator it;
		for(it = g.begin(); it != g.end(); ++it)
			*it = source->rand();
	}

	template class OpInitRand<uint64_t>;
	template class OpInitRand<double>;
}
