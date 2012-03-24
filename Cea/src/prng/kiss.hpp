/*
   KISS generator formed from 2 XOR shifts,
   an LCG and a MWC.
   + Period: ~= 3.1 x 10^57
   + Speed: Slow (~0.6x)
*/
#ifndef CEA_KISS_HPP
#define CEA_KISS_HPP

// Parameter definitions.
namespace prng_kiss_internal
{
    const uint64_t A = 3202034522624059733ULL;
    const uint64_t C = 2691343689449507681ULL;

    const int S11 = 20;
    const int S12 = 41;
    const int S13 = 5;
    const int S21 = 21;
    const int S22 = 35;
    const int S23 = 4;

    const uint32_t M = 3874257210U;

    const uint64_t V0 = 2685821657736338717ULL;
    const uint64_t W0 = 1;;

    class prng_kiss : public prng
    {
        public:
            prng_kiss(uint64_t seed = 1)
            {
                srand(seed);
            }

            uint64_t rand()
            {
                // LCG
                u = A * u + C;

                // First XOR shift.
                v ^= (v << S11);
                v ^= (v >> S12);
                v ^= (v << S13);

                // MWC
                w = M*(w & 0xFFFFFFFF) + (w >> 32);

                // Second XOR shift into temporary value.
                uint64_t t = u ^ (u >> S21);
                t ^= (t << S22);
                t ^= (t >> S23);
                return (t ^ v) + w;
            }

            void srand(uint64_t seed)
            {
                v = V0; w = W0;
                // Don't want a 0 state.
                u = seed == v ? 1 : seed ^ v;
                rand();
                v = u; rand();
                w = v; rand();
            }

        private:
            // State
            uint64_t u, v, w;
    };
}

using prng_kiss_internal::prng_kiss;

#endif // CEA_KISS_HPP
