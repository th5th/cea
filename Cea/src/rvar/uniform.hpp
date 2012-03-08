// Uniform distribution.
#ifndef CEA_UNIFORM_HPP
#define CEA_UNIFORM_HPP

template <typename T>
class RVarUniform : public RVar<T>
{
    public:
        // Constructors
        RVarUniform(Prng * src, T a = 0, T b = 0)
        {
            if(a != 0 || b != 0)
                set_interval(a, b);

            set_source(src);
        }

        void set_interval(T a, T b)
        {
            lower = a < b ? a : b;
            upper = a > b ? a : b;
            // deal with a == b
        }

        void set_source(Prng * src)
        {
            source = src;
        }

        // Use type traits to determine which (private) implementation to use.
        T rand()
        {
            return rand_impl(std::is_arithmetic<T>(), std::is_floating_point<T>());
        }

    private:
        // Typed rand() overloads.
        inline T rand_impl(std::true_type, std::true_type)
        {
            T temp = static_cast<T>(source->rand()) / static_cast<T>(std::numeric_limits<uint64_t>::max());
            return lower + (temp * (upper - lower));
        }

        inline T rand_impl(std::true_type, std::false_type)
        {
            return static_cast<T>(lower + (source->rand() % (upper - lower)));
        }

        // Bounds
        T lower;
        T upper;

        // PRNG
        Prng * source;
};

#endif // CEA_UNIFORM_HPP