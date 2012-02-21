#include <cea-rand.h>

namespace cea
{
	template <typename T>
	RVarUniform<T>::RVarUniform(Prng * src, uint64_t seed)
	{
		set_source(src);
		srand(seed);
	}

	template <typename T>
	void RVarUniform<T>::set_interval(T a, T b)
	{
		if(a < b)
		{
			lower = a;
			upper = b;
		}
		else
		{
			lower = b;
			upper = a;
		}
	}

	template <typename T>
	void RVarUniform<T>::set_source(Prng * src)
	{
		source = src;
	}

	template <typename T>
	void RVarUniform<T>::srand(uint64_t seed)
	{
		source->srand(seed);
	}

	template <>
	uint64_t RVarUniform<uint64_t>::rand()
	{
		uint64_t rv =  source->rand() % (upper - lower);
		return rv + lower;
	}
	
	template <>
	double RVarUniform<double>::rand()
	{
		double rv = static_cast<double>(source->rand()) / UINT64_MAX;
		rv *= (upper - lower);
		return rv + lower;
	}

	template class RVarUniform<uint64_t>;
	template class RVarUniform<double>;

}
