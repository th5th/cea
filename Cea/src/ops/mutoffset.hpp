// Offset mutator.
#ifndef CEA_MUTOFFSET_HPP
#define CEA_MUTOFFSET_HPP

template <typename T, typename U, typename Enable = void>
class OpMutOffset;

template <typename T, typename U>
class OpMutOffset <T, U, typename std::enable_if< std::is_floating_point<U>::value >::type> : public OpGenome<T>
{
    public:
        // Constructors.
        OpMutOffset(U p, RVar<T> * m_src, RVar<U> * p_src)
            : p_mut(p), mut_source(m_src), prob_source(p_src) { }

    private:
        U p_mut;
        RVar<T> * mut_source;
        RVar<U> * prob_source;

        void apply_tog(Genome<T>& g)
        {
            for(unsigned int i = 0; i < g.size(); ++i)
            {
                if(prob_source->rand() < p_mut)
                {
                    g[i] += mut_source->rand();
                }
            }
        }
};
           
#endif // CEA_MUTOFFSET_HPP

