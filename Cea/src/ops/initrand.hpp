// Random initialiser
#ifndef CEA_INITRAND_H
#define CEA_INITRAND_H

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
            typename std::vector<T>::iterator it;
            for(it = g.begin(); it != g.end(); ++it)
                *it = source->rand();
        }
};

#endif // CEA_INITRAND_H
