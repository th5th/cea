#include <cea-rand.h>

namespace cea
{
	RVarUniform::RVarUniform(uint64_t seed, Prng * src)
	{
		set_source(src);
		srand(seed);
	}

	void RVarUniform::set_source(Prng * src)
	{
		source = src;
	}

	void RVarUniform::srand(uint64_t seed)
	{
		source->srand(seed);
	}

	double RVarUniform::rand()
	{
		return (static_cast<double>(source->rand()) / UINT64_MAX);
	}
}
