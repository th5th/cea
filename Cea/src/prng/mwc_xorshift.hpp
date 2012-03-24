/*
   Generator combining an XOR shift with an MWC generator.
   + Period: ~= 8.5 x 10^37 (~10^19x)
   + Speed: Medium (~0.8x)
*/
#ifndef CEA_MWC_XORSHIFT_HPP
#define CEA_MWC_XORSHIFT_HPP

// Parameter definitions.
namespace prng_mwc_xorshift_internal
{
    const int S1 = 20;
    const int S2 = 41;
    const int S3 = 5;

    const uint32_t M = 1640531364U;

    const uint64_t X0 = 4101842887655102017ULL;

    class prng_mwc_xorshift : public prng
    {
        public:
            prng_mwc_xorshift(uint64_t seed = 1)
            {
                srand(seed);
            }

            uint64_t rand()
            {
                x ^= (x << S1);
                x ^= (x >> S2);
                x ^= (x << S3);
                y = M * (y & 0xFFFFFFFF) + (y >> 32);
                return x ^ y;
            }

            void srand(uint64_t seed)
            {
                x = (seed == X0 ? 1 : seed ^ X0);
                y = 1;
                y = rand();
                x = rand();
            }

        private:
            uint64_t x, y;
    };
}

using prng_mwc_xorshift_internal::prng_mwc_xorshift;

#endif // CEA_MWC_XORSHIFT_HPP
