// Debug initialiser.
#ifndef CEA_INIT_DEBUG_HPP
#define CEA_INIT_DEBUG_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class op_init_debug
{
    public:
        // Set jth el of ith individual to i*j.
        // Set fitness of ith individual to i.
        void operator()(pop<COuter,CInner,T>& p)
        {
            int i = 0;
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it, ++i)
            {
                p_it->alive(true);
                p_it->evald(true);
                p_it->fitness(static_cast<double>(i));
                auto g_it = p_it->begin();
                int j = 0;
                for(; g_it != p_it->end(); ++g_it, ++j)
                {
                    *g_it = i*j;
                }
            }
        }
};

#endif // CEA_INIT_DEBUG_HPP
