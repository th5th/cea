// Support class to generate pseudo random numbers.
#ifndef CEA_PRNG_HPP
#define CEA_PRNG_HPP

class prng
{
    public:
        virtual void srand(uint64_t seed) = 0;
        virtual uint64_t rand() = 0;
};

#endif // CEA_PRNG_HPP
