// Random initialiser
#ifndef CEA_INIT_RAND_HPP
#define CEA_INIT_RAND_HPP

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class op_init_rand
{
    public:
        op_init_rand(rvar<T> * src) : source(src) { }

        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                p_it->alive(true);
                auto g_it = p_it->begin();
                for(; g_it != p_it->end(); ++g_it)
                {
                    *g_it = source->rand();
                }
            }
        }

    private:
        rvar<T> * source;
};

#endif // CEA_INIT_RAND_HPP
