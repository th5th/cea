// Support class to generate pseudo random numbers.
#ifndef CEA_RVAR_HPP
#define CEA_RVAR_HPP

template <typename T>
class rvar
{
    public:
        virtual T rand() = 0;
};

#endif // CEA_RVAR_HPP
