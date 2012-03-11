// Wrapper for OpGenome which removes its
// abstractness and provides construction
// from a function pointer or callable.
#ifndef CEA_OPEVALFITNESS_HPP
#define CEA_OPEVALFITNESS_HPP

template <typename T>
class OpEvalFitness: public OpGenome<T>
{
    public:
        OpEvalFitness( double (*f)(Genome<T> const &) ) : ff(f) {}
        OpEvalFitness(std::function<double(Genome<T> const&)> f) : ff(f) {}

        void set_fn( double (*f)(Genome<T> const &) )
        {
            ff = f;
        }

        void set_fn(std::function<double(Genome<T> const&)> f)
        {
            ff = f;
        }

    private:
        std::function<double(Genome<T> const&)> ff;

        void apply_tog(Genome<T>& g)
        {
            if(!g.evald)
            {
                g.fitness = ff(g);
                g.evald = true;
            }
        }
};

#endif // CEA_OPEVALFITNESS_HPP
