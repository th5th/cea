#include <cea-rand.h>

namespace cea
{
	// Parameters for this PRNG.
	// XOR shift parameters.
	const uint32_t S1 = 20;
	const uint32_t S2 = 41;
	const uint32_t S3 = 5;
	// MWC multiplier.
	const uint32_t M = 1640531364;
	const uint64_t X0 = 4101842887655102017;

	PrngMWCXORShift::PrngMWCXORShift(uint64_t seed)
	{
		srand(seed);
	}
	
	uint64_t PrngMWCXORShift::rand()
	{
		x ^= (x << S1); x ^= (x >> S2); x ^= (x << S3);
		y = M * (y & 0xFFFFFFFF) + (y >> 32);
		return x ^ y;
	}

	void PrngMWCXORShift::srand(uint64_t seed)
	{
		x = (seed == X0 ? 1 : seed ^ X0);
		y = 1;
		y = rand();
		x = rand();
	}

}
