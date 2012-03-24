/*
   Generator combining an XOR shift with an MWC generator.
   + Period: ~= 8.5 x 10^37 (~10^19x)
   + Speed: Medium (~0.8x)
*/
#ifndef CEA_MWC_XORSHIFT_HPP
#define CEA_MWC_XORSHIFT_HPP

// Parameter definitions.
namespace mwc_xorshift
{

    const uint32_t S1 = 20;
    const uint32_t S2 = 41;
    const uint32_t S3 = 5;

    const uint32_t M = 1640531364;
    const uint64_t X0 = 4101842887655102017;
}

class prng_mwc_xorshift : public prng
{
    public:
        prng_mwc_xorshift(uint64_t seed = 1)
        {
            srand(seed);
        }

        uint64_t rand()
        {
            x ^= (x << mwc_xorshift::S1);
            x ^= (x >> mwc_xorshift::S2);
            x ^= (x << mwc_xorshift::S3);
            y = mwc_xorshift::M * (y & 0xFFFFFFFF) + (y >> 32);
            return x ^ y;
        }

        void srand(uint64_t seed)
        {
            x = (seed == mwc_xorshift::X0 ? 1 : seed ^ mwc_xorshift::X0);
            y = 1;
            y = rand();
            x = rand();
        }

    private:
        uint64_t x, y;
};

#endif // CEA_MWC_XORSHIFT_HPP
