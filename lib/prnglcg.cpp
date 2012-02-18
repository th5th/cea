/*
   prnglcg.cpp

   Implementation of a 64-bit linear congruential
   generator (LCG) using Donald Knuth's coefficients
   from MMIX. Reference required!
*/

#include <cstdint>

#include <cea-rand.h>

namespace cea
{
	const uint64_t A = 6364136223846793005;
	const uint64_t C = 1442695040888963407;

	PrngLCG::PrngLCG(uint64_t seed)
	{
		srand(seed);
	}

	void PrngLCG::srand(uint64_t seed)
	{
		x = seed;
	}

	uint64_t PrngLCG::rand()
	{
		x = static_cast<uint64_t>(A*x + C);
		return x;
	}
}
