// Support class to generate pseudo random numbers.
#ifndef CEA_RVAR_H
#define CEA_RVAR_H

template <typename T>
class RVar
{
    public:
        virtual T rand() = 0;
};

#endif // CEA_RVAR_H
