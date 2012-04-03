// Pretty printer for populations.
//
// Limited to debugging really, since printing large
// data sets to the console is impractical.
#ifdef CEA_DEBUG
#ifndef CEA_PRINT_HPP
#define CEA_PRINT_HPP

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class print
{
    public:
        print(unsigned int w) : width(w) { }

        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                auto g_it = p_it->begin();
                for(; g_it != p_it->end(); ++g_it)
                {
                    std::cout.width(width);
                    std::cout.precision(2);
                    std::cout << std::fixed << *g_it;
                }
                std::cout << " |";
                // Output such flags as are available.
                if(p_it->alive() == false)
                {
                    std::cout.width(2);
                    std::cout << p_it->alive();
                    std::cout.width(2);
                    std::cout << "-";
                    std::cout.width(width);
                    std::cout << "-" << std::endl;
                }
                else if(p_it->evald() == false)
                {
                    std::cout.width(2);
                    std::cout << p_it->alive();
                    std::cout.width(2);
                    std::cout << p_it->evald();
                    std::cout.width(width);
                    std::cout << "-" << std::endl;
                }
                else
                {
                    std::cout.width(2);
                    std::cout << p_it->alive();
                    std::cout.width(2);
                    std::cout << p_it->evald();
                    std::cout.width(width);
                    std::cout << p_it->fitness() << std::endl;
                }
            }
            std::cout << std::endl;
        }

    private:
        unsigned int width;
};

#endif // CEA_PRINT_HPP
#endif // CEA_DEBUG
