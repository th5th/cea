#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

const double P_SEL = 0.05;

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class zero_init
{ 
    public:
        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                p_it->alive(true);
                p_it->evald(true);
                p_it->fitness(0.0);
                auto g_it = p_it->begin();
                for(; g_it != p_it->end(); ++g_it)
                {
                    *g_it = static_cast<T>(0.0);
                }
            }
        }
};

template <template <typename,typename> class COuter,
         template <typename,typename> class CInner,
         typename T>
class mut_checker
{
    public:
        mut_checker(bool& res, std::vector<T> const& mv,
            std::vector<double> const& mp)
            : result(res), mut_vals(mv), mut_probs(mp) { } 

        void operator()(pop<COuter,CInner,T>& p)
        {
            int j = 0;
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                bool modified = false; // Set false for each genome.
                auto g_it = p_it->begin();
                for(int i = 0; g_it != p_it->end(); ++g_it, ++i)
                {
                    double p = mut_probs[i];
                    T val = mut_vals[j];
                    if(p < P_SEL) // Gene modified.
                    {
                        j = ++j > 9 ? 0 : j;
                        modified = true;
                        if(*g_it != val)
                        {
                            // Error
                            std::cout << " | Gene should have been "
                                "modified, but was not: ";
                            std::cout << *g_it << " != " << val;
                            std::cout << std::endl;
                            result = true;
                        }

                    }
                    else // Gene not modified.
                    {
                        if(*g_it != static_cast<T>(0))
                        {
                            // Error
                            std::cout << " | Gene should not have been "
                                "modified, but was: ";
                            std::cout << "*g_it == " << *g_it << std::endl;
                            result = true;
                        }
                    }
                }

                // Check genome flags.
                if(modified)
                {
                    // Check flags.
                    // Short-circuit operator makes sure
                    // no exceptions will be thrown here.
                    if(!(p_it->alive() == true && p_it->evald() == false))
                    {
                        // Error
                        std::cout << " | Genome flags were incorrect "
                            "for genome with modified gene.";
                        std::cout << std::endl;
                        result = true;
                    }
                }
                else
                {
                    // Check flags.
                    if(!(p_it->alive() == true && p_it->evald() == true &&
                        p_it->fitness() == 0.0))
                    {
                        // Error
                        std::cout << " | Genome flags were incorrect "
                            "for genome with unmodified genes.";
                        std::cout << std::endl;
                        result = true;
                    }
                }
            }
        }

    private:
        bool& result;
        std::vector<T> const& mut_vals;
        std::vector<double> const& mut_probs;
};

bool test_mut_offset()
{
    obj_fact<std::vector, std::list, float> fact;
    auto alg_obj = fact.get<alg>(10,10);

    alg_obj.push_back(fact.get<zero_init>());

    // Values added to gene if mut_probs[i] < P_SEL.
    std::vector<float> mut_vals = {0.1,-0.1,0.2,-0.2,0.3,
        -0.3,0.4,-0.4,0.5,-0.5};
    rvar_debug<float> rv(mut_vals);
    std::vector<double> mut_probs = {0.1,0.01,0.2,0.7,0.5,
        0.03,0.08,0.4,0.59,0.91};
    rvar_debug<double> rp(mut_probs);
    alg_obj.push_back(fact.get<op_mut_offset>(&rv,&rp,P_SEL));

    bool test_failed = false;
    auto mc = fact.get<mut_checker>(test_failed,mut_vals,mut_probs);
    alg_obj.push_back(mc);

    alg_obj.run_once();

    return test_failed;
}
