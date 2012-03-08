/*
   Generator combining an XOR shift with an MWC generator.
   + Period: ~= 8.5 x 10^37 (~10^19x)
   + Speed: Medium (~0.8x)
*/
#ifndef CEA_MWCXORS_H
#define CEA_MWCXORS_H

class PrngMWCXORShift : public Prng
{
    public:
        PrngMWCXORShift(uint64_t seed = 1)
        {
            srand(seed);
        }

        uint64_t rand()
        {
            x ^= (x << S1); x ^= (x >> S2); x ^= (x << S3);
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

        // PRNG component paramters
        // XOR shift parameters.
        const static uint32_t S1, S2, S3;
        // MWC multiplier.
        const static uint32_t M;
        const static uint64_t X0;
};

// Parameter definitions.
const uint32_t PrngMWCXORShift::S1 = 20;
const uint32_t PrngMWCXORShift::S2 = 41;
const uint32_t PrngMWCXORShift::S3 = 5;

const uint32_t PrngMWCXORShift::M = 1640531364;
const uint64_t PrngMWCXORShift::X0 = 4101842887655102017;

#endif // CEA_MWCXORS_H
