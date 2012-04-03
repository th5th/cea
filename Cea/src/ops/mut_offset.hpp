// Offset mutator.
#ifndef CEA_MUT_OFFSET_HPP
#define CEA_MUT_OFFSET_HPP

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class op_mut_offset
{
    public:
        op_mut_offset(rvar<T> * v_src, rvar<double> * p_src, double p)
            : val_source(v_src), prob_source(p_src), p_mut(p) { }

        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                auto g_it = p_it->begin();
                for(; g_it != p_it->end(); ++g_it)
                {
                    if(prob_source->rand() < p_mut)
                    {
                        p_it->evald(false);
                        *g_it += val_source->rand();
                    }
                }
            }
        }

    private:
        rvar<T> * val_source;
        rvar<double> * prob_source;
        double p_mut;
};
           
#endif // CEA_MUT_OFFSET_HPP

