/*
   Generator formed from an XOR shift and an MLCG.
   + Period: ~=1.8 x 10^19 (1x)
   + Speed: Fast (1x)
*/
#ifndef CEA_MLCG_XORSHIFT_HPP
#define CEA_MLCG_XORSHIFT_HPP

// Parameter definitions.
namespace prng_mlcg_xorshift_internal
{
    const uint64_t A = 7664345821815920749ULL;

    const int S1 = 17;
    const int S2 = 31;
    const int S3 = 8;

    const uint64_t X0 = 3935559000370003845ULL;

    class prng_mlcg_xorshift : public prng
    {
        public:
            prng_mlcg_xorshift(uint64_t seed = 1)
            {
                srand(seed);
            }

            uint64_t rand()
            {
                x ^= (x << S1);
                x ^= (x >> S2);
                x ^= (x << S3);
                return A * x;
            }

            void srand(uint64_t seed)
            {
                x = seed == X0 ? 1 : seed ^ X0;
                x = rand();
            }

        private:
            // State
            uint64_t x;
    };
}

using prng_mlcg_xorshift_internal::prng_mlcg_xorshift;

#endif // CEA_MLCG_XORSHIFT_HPP
