#include <cea-rand.h>

namespace cea
{
	template <typename T>
	RVarUniform<T>::RVarUniform(Prng * src, T a, T b)
	{
		if(a != 0 || b != 0)
			set_interval(a, b);

		set_source(src);
	}

	template <typename T>
	void RVarUniform<T>::set_interval(T a, T b)
	{
		lower = a < b ? a : b;
		upper = a > b ? a : b;
		// deal with a == b
	}

	template <typename T>
	void RVarUniform<T>::set_source(Prng * src)
	{
		source = src;
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
