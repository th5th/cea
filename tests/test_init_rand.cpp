#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class value_checker
{
    public:
        value_checker(bool& res, rvar<T> * src)
            : result(res), source(src) { }

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
                    if(p_it->alive() == false)
                    {
                        std::cout << " | alive() should return true." << std::endl;
                        result = true;
                    }

                    // evald should be false.
                    if(p_it->evald() == true)
                    {
                        std::cout << " | evald() should return false." << std::endl;
                        result = true;
                    }
                }
                catch(std::runtime_error& e)
                {
                    std::cout << " | Caught exception: " << e.what() << std::endl;
                    result = true;
                }

                auto g_it = p_it->begin();
                for(; g_it != p_it->end(); ++g_it)
                {
                    if(*g_it != source->rand())
                    {
                        std::cout << " | Data does not match." << std::endl;
                        result = true;
                    }
                }
            }
        }
    private:
        bool& result;
        rvar<T> * source;
};

bool test_init_rand()
{
    obj_fact<std::vector, std::vector, float> fact;
    auto alg_obj = fact.get<alg>(16,6);

    // Two identically seeded PRNGs.
    prng_kiss prng1, prng2;
    rvar_uniform<float> r1(&prng1, -2.0, 2.0);
    rvar_uniform<float> r2(&prng2, -2.0, 2.0);

    alg_obj.push_back(fact.get<op_init_rand>(&r1));

    bool test_failed = false;
    alg_obj.push_back(fact.get<value_checker>(test_failed,&r2));

    alg_obj.run_once();

    return test_failed;
}
