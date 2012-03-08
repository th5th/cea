/*
   Generator formed from an XOR shift and an MLCG.
   + Period: ~=1.8 x 10^19 (1x)
   + Speed: Fast (1x)
*/
#ifndef CEA_MLCGXORS_HPP
#define CEA_MLCGXORS_HPP

// Parameter definitions.
namespace xorshift
{
    const uint64_t A = 7664345821815920749;

    const uint32_t S1 = 17;
    const uint32_t S2 = 31;
    const uint32_t S3 = 8;

    const uint64_t X0 = 3935559000370003845;
}

class PrngMLCGXORShift : public Prng
{
    public:
        PrngMLCGXORShift (uint64_t seed = 1)
        {
            srand(seed);
        }

        uint64_t rand()
        {
            x ^= (x << xorshift::S1);
            x ^= (x >> xorshift::S2);
            x ^= (x << xorshift::S3);
            return xorshift::A * x;
        }

        void srand(uint64_t seed)
        {
            x = seed == xorshift::X0 ? 1 : seed ^ xorshift::X0;
            x = rand();
        }

    private:
        // State
        uint64_t x;
};

#endif // CEA_MLCGXORS_HPP
