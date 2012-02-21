// OpGenome shortcut class.
#include <cea.h>

namespace cea
{
	template <typename T>
	void OpGenome<T>::apply_to(Pop<T>& p)
	{
		typename std::vector< Genome<T> >::iterator it;
		for(it = p.begin(); it != p.end(); ++it)
			apply_tog(*it);
	}

	template class OpGenome<uint64_t>;
	template class OpGenome<double>;
}
