// Random initialiser
#ifndef CEA_INITRAND_HPP
#define CEA_INITRAND_HPP

template <typename T>
class OpInitRand : public OpGenome<T>
{
    public:
        // Constructor.
        OpInitRand(RVar<T> * src)
        {
            source = src;
        }

    private:
        RVar<T>* source;

        void apply_tog(Genome<T>& g)
        {
            g.fitness = 0.0;
            g.avail = false;
            g.evald = false;
            for(uint64_t i = 0; i < g.size(); ++i)
            {
                g[i] = source->rand();
            }
        }
};

#endif // CEA_INITRAND_HPP
