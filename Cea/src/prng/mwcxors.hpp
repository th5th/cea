/*
   Generator combining an XOR shift with an MWC generator.
   + Period: ~= 8.5 x 10^37 (~10^19x)
   + Speed: Medium (~0.8x)
*/
#ifndef CEA_MWCXORS_HPP
#define CEA_MWCXORS_HPP

// Parameter definitions.
namespace mwcxors
{

    const uint32_t S1 = 20;
    const uint32_t S2 = 41;
    const uint32_t S3 = 5;

    const uint32_t M = 1640531364;
    const uint64_t X0 = 4101842887655102017;
}

class PrngMWCXORShift : public Prng
{
    public:
        PrngMWCXORShift(uint64_t seed = 1)
        {
            srand(seed);
        }

        uint64_t rand()
        {
            x ^= (x << mwcxors::S1);
            x ^= (x >> mwcxors::S2);
            x ^= (x << mwcxors::S3);
            y = mwcxors::M * (y & 0xFFFFFFFF) + (y >> 32);
            return x ^ y;
        }

        void srand(uint64_t seed)
        {
            x = (seed == mwcxors::X0 ? 1 : seed ^ mwcxors::X0);
            y = 1;
            y = rand();
            x = rand();
        }

    private:
        uint64_t x, y;
};

#endif // CEA_MWCXORS_HPP
