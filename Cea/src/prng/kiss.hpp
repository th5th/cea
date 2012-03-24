/*
   KISS generator formed from 2 XOR shifts,
   an LCG and a MWC.
   + Period: ~= 3.1 x 10^57
   + Speed: Slow (~0.6x)
*/
#ifndef CEA_KISS_HPP
#define CEA_KISS_HPP

// Parameter definitions.
namespace kiss
{
    const uint64_t A = 3202034522624059733;
    const uint64_t C = 2691343689449507681;

    const uint32_t S11 = 20;
    const uint32_t S12 = 41;
    const uint32_t S13 = 5;
    const uint32_t S21 = 21;
    const uint32_t S22 = 35;
    const uint32_t S23 = 4;

    const uint32_t M = 3874257210U;

    const uint64_t V0 = 2685821657736338717;
    const uint64_t W0 = 1;;
}

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
            u = kiss::A * u + kiss::C;
            // First XOR shift.
            v ^= v << kiss::S11; v ^= v >> kiss::S12; v ^= v << kiss::S13;
            // MWC
            w = kiss::M*(w & 0xFFFFFFFF) + (w >> 32);
            // Second XOR shift into temporary value.
            uint64_t t = u ^ (u >> kiss::S21); t ^= (t << kiss::S22); t ^= (t >> kiss::S23);
            return (t ^ v) + w;
        }

        void srand(uint64_t seed)
        {
            v = kiss::V0; w = kiss::W0;
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


#endif // CEA_KISS_HPP
