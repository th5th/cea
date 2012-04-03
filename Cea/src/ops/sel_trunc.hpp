// Simple truncation selection algorithm.
// Selects strongest P% of the population and
// marks them as available.
#ifndef CEA_SEL_TRUNC_HPP
#define CEA_SEL_TRUNC_HPP

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class op_sel_trunc
{
    public:
        op_sel_trunc(double pc)
        {
            if(pc < 0.0 || pc > 1.0)
            {
                throw(std::invalid_argument("Selection rate must "
                    "be in [0,1] in OpSelTruncation."));
            }
            else
            {
                sel_pc = pc;
            }
        }

        void operator()(pop<COuter,CInner,T>& p)
        {
            // TODO Make op_sel_trunc work properly with non-RA iterators.
            // TODO Implementation reorders the population - desirable? 
            unsigned int k = std::round((1.0 - sel_pc) * p.size());
            std::nth_element(p.begin(), p.begin()+k, p.end());
            auto p_it = p.begin();
            for(; p_it != p.begin()+k; ++p_it)
            {
                // genome ensures evald() is false after this call.
                p_it->alive(false);
            }
        }

    private:
        double sel_pc;
};

#endif // CEA_SELTRUNCATION_HPP
