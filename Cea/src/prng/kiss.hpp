/*
   KISS generator formed from 2 XOR shifts,
   an LCG and a MWC.
   + Period: ~= 3.1 x 10^57
   + Speed: Slow (~0.6x)
*/
#ifndef CEA_KISS_H
#define CEA_KISS_H

class PrngKISS : public Prng
{
    public:
        PrngKISS(uint64_t seed = 1)
        {
            srand(seed);
        }

        uint64_t rand()
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

        // PRNG component paramters
        // LCG parameters.
        const static uint64_t A, C;
        // XOR shift params (2 sets).
        const static uint32_t S11 , S12 , S13 , S21 , S22 , S23;
        // MWC Multiplier.
        const static uint32_t M;
        // Initial state values.
        const static uint64_t V0, W0;

};

// Parameter definitions.
const uint64_t PrngKISS::A = 3202034522624059733;
const uint64_t PrngKISS::C = 2691343689449507681;

const uint32_t PrngKISS::S11 = 20;
const uint32_t PrngKISS::S12 = 41;
const uint32_t PrngKISS::S13 = 5;
const uint32_t PrngKISS::S21 = 21;
const uint32_t PrngKISS::S22 = 35;
const uint32_t PrngKISS::S23 = 4;

const uint32_t PrngKISS::M = 3874257210U;

const uint64_t PrngKISS::V0 = 2685821657736338717;
const uint64_t PrngKISS::W0 = 1;

#endif // CEA_KISS_H
