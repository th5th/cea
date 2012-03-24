// Uniform distribution.
#ifndef CEA_UNIFORM_HPP
#define CEA_UNIFORM_HPP

template <typename T>
class rvar_uniform : public rvar<T>
{
    public:
        // Constructors
        rvar_uniform(prng * src, T a = 0, T b = 10) : source(src)
        {
            set_interval(a, b);
        }

        void set_interval(T a, T b)
        {
            if(a == b)
            {
                throw(std::invalid_argument("Bounds on RVarUniform"
                    " cannot be equal."));
            }
            lower = a < b ? a : b;
            upper = a > b ? a : b;
        }

        void set_source(prng * src)
        {
            source = src;
        }

        // Type dependent implementation.
        T rand()
        {
            return rand_impl(std::is_arithmetic<T>(),
                std::is_floating_point<T>());
        }

    private:
        // Floating-point overload.
        inline T rand_impl(std::true_type, std::true_type)
        {
            T temp = static_cast<T>(source->rand()) /
                static_cast<T>(std::numeric_limits<uint64_t>::max());
            return lower + (temp * (upper - lower));
        }

        // Integer overload.
        inline T rand_impl(std::true_type, std::false_type)
        {
            return static_cast<T>(lower + (source->rand() %
                (upper - lower)));
        }

        // Bounds
        T lower;
        T upper;

        // PRNG
        prng * source;
};

#endif // CEA_UNIFORM_HPP
