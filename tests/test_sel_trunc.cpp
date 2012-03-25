#include <iostream>
#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class value_checker
{
    public:
        value_checker(bool& res, double ps) : result(res), p_sel(ps) { }

        // Check contents against that generated by source.
        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                // Check flag statuses.
                try
                {
                    // alive should be true.
                    if(p_it->alive() == true && p_it->evald() == true)
                    {
                        // Individual survived.
                        if(p_it->fitness() < std::round((1.0-p_sel)*p.size()))
                        {
                            std::cout << " | Found survivor with fitness"
                                " less than the top " << p_sel*100 << "% of"
                                " the population." << std::endl;
                            result = true;
                        }
                    }
                    else if(p_it->alive() == false)
                    {
                        // Culled.
                    }
                    else
                    {
                        std::cout << " | Found genome with incompatible set"
                            " of post-selection flags." << std::endl;
                        result = true;
                    }
                }
                catch(std::exception& e)
                {
                    std::cout << " | Caught exception: ";
                    std::cout << e.what() << std::endl;
                    result = true;
                }
            }
        }
    private:
        bool& result;
        double p_sel;
};

bool test_sel_trunc()
{
    double p_sel = 0.36;
    bool test_failed = false;
    alg<std::vector, std::vector, double> alg(13,10);
    // 13*0.36 gives 5 individuals to accept, 8 to reject.

    alg.make_push_back<op_init_debug>();
    try
    {
        alg.make_push_back<op_sel_trunc>(-15.4);
    }
    catch(std::exception& e)
    {
        std::cout << " | Caught exception: " << e.what() << std::endl;
    }
    alg.make_push_back<op_sel_trunc>(p_sel);
    alg.make_push_back<value_checker>(test_failed, p_sel);
    
    alg.run_once();

    return test_failed;
}
