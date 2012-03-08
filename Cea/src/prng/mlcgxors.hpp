/*
   Generator formed from an XOR shift and an MLCG.
   + Period: ~=1.8 x 10^19 (1x)
   + Speed: Fast (1x)
*/
#ifndef CEA_MLCGXORS_H
#define CEA_MLCGXORS_H

class PrngMLCGXORShift : public Prng
{
    public:
        PrngMLCGXORShift (uint64_t seed = 1)
        {
            srand(seed);
        }

        uint64_t rand()
        {
            x ^= (x << S1); x ^= (x >> S2); x ^= (x << S3);
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

        // PRNG component parameters.
        // XOR shift parameters.
        const static uint32_t S1, S2, S3;
        // MLCG multiplier.
        const static uint64_t A, X0;
};

// Parameter definitions.
const uint32_t PrngMLCGXORShift::S1 = 17;
const uint32_t PrngMLCGXORShift::S2 = 31;
const uint32_t PrngMLCGXORShift::S3 = 8;

const uint64_t PrngMLCGXORShift::A = 7664345821815920749;
const uint64_t PrngMLCGXORShift::X0 = 3935559000370003845;

#endif // CEA_MLCGXORS_H
