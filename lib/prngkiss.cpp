/*
   KISS generator formed from 2 XOR shifts,
   and LCG and a MWC.
   + Period: ~= 3.1 x 10^57
   + Speed:
 */

#include <cea-rand.h>

namespace cea
{
	// Parameters for this PRNG.
	// LCG parameters.
	const uint64_t A = 3202034522624059733;
	const uint64_t C = 2691343689449507681;;
	// XOR shift params (2 sets).
	const uint32_t S11 = 20;
	const uint32_t S12 = 41;
	const uint32_t S13 = 5;
	const uint32_t S21 = 21;
	const uint32_t S22 = 35;
	const uint32_t S23 = 4;
	// MWC Multiplier.
	const uint32_t M = 3874257210U;
	// Initial state values.
	const uint64_t V0 = 2685821657736338717;
	const uint64_t W0 = 1;

	PrngKISS::PrngKISS(uint64_t seed)
	{
		srand(seed);
	}

	uint64_t PrngKISS::rand()
	{
		// LCG
		u = A * u + C;
		// First XOR shift.
		v ^= v << S11; v ^= v >> S12; v ^= v << S13;
		// MWC
		w = M*(w & 0xFFFFFFFF) + (w >> 32);
		// Second XOR shift into temporary value.
		uint64_t t = u ^ (u >> S21); t ^= (t << S22); t ^= (t >> S23);
		return (t ^ v) + w;
	}

	void PrngKISS::srand(uint64_t seed)
	{
		v = V0; w = W0;
		// Don't want a 0 state.
		u = seed == v ? 1 : seed ^ v;
	       	rand();
		v = u; rand();
		w = v; rand();
	}
}
