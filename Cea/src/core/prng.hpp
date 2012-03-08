// Support class to generate pseudo random numbers.
#ifndef CEA_PRNG_H
#define CEA_PRNG_H

class Prng
{
    public:
        virtual void srand(uint64_t seed) = 0;
        virtual uint64_t rand() = 0;
};

#endif // CEA_PRNG_H
