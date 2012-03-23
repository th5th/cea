// Pretty printer for populations.
//
// Limited to debugging really, since printing large
// data sets to the console is impractical.
//
// Note if used alone in a cea object, print() will be
// called indefinitely, as it does not set p.running(false).
#ifdef CEA_DEBUG
#ifndef CEA_PRINT_HPP
#define CEA_PRINT_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class print
{
    public:
        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            std::cout << p.size() << std::endl;
            std::cout << p_it->size() << std::endl;

            for(; p_it != p.end(); ++p_it)
            {
                auto it_gvf = p_it->begin();
                for(; it_gvf != p_it->end(); ++it_gvf)
                {
                    std::cout << *it_gvf;
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
};

#endif // CEA_PRINT_HPP
#endif // CEA_DEBUG
