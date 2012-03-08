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
            g.set_fitness(0.0);
            g.set_avail(false);
            g.set_evald(false);
            typename std::vector<T>::iterator it;
            for(it = g.begin(); it != g.end(); ++it)
                *it = source->rand();
        }
};

#endif // CEA_INITRAND_HPP
