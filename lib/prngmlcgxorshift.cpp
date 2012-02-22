#include <cea-rand.h>

namespace cea
{
	// Parameters for this PRNG.
	// XOR shift parameters.
	const uint32_t S1 = 17;
	const uint32_t S2 = 31;
	const uint32_t S3 = 8;
	// MLCG multiplier.
	const uint64_t A = 7664345821815920749;
	const uint64_t X0 = 3935559000370003845;

	PrngMLCGXORShift::PrngMLCGXORShift(uint64_t seed)
	{
		srand(seed);
	}
	
	uint64_t PrngMLCGXORShift::rand()
	{
		x ^= (x << S1); x ^= (x >> S2); x ^= (x << S3);
		return A * x;
	}

	void PrngMLCGXORShift::srand(uint64_t seed)
	{
		x = seed == X0 ? 1 : seed ^ X0;
		x = rand();
	}

}
