#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;
using std::chrono::milliseconds;

void point_spread(pop<std::vector,std::vector,double>& p)
{
    auto p_it = p.begin();
    for(; p_it != p.end(); ++p_it)
    {
        if(p_it->evald() == false)
        {
            // Sort the genes.
            std::sort(p_it->begin(), p_it->end());

            auto point_it = p_it->begin();
            double d_mean = 0.0;

            for(unsigned int i = 0; i < p_it->size(); ++i)
            {
                // Make sure points stay in [0.0,10.0].
                point_it[i] = point_it[i] < 0.0 ? 0.0 : point_it[i];
                point_it[i] = point_it[i] > 10.0 ? 10.0 : point_it[i];

                d_mean += std::abs(point_it[i] - static_cast<double>(i));;
            }

            p_it->evald(true);
            p_it->fitness(static_cast<double>(p_it->size())/d_mean);
        }
    }
}

bool test_point_spread()
{
    obj_fact<std::vector,std::vector,double> fact;
    auto alg_obj = fact.get<alg>(16,10);

    prng_kiss p1;
    // Arrange points randomly along line from 0 to 10.
    rvar_uniform<double> r1(&p1, 0.0, 10.0);
    alg_obj.push_back(fact.get<op_init_rand>(&r1));
    alg_obj.run_once();

    alg_obj.clear();

    // Truncation selector - best 50%.
    alg_obj.push_back(fact.get<op_sel_trunc>(0.5));

    // Generator and op for 1-point crossover.
    prng_kiss p2;
    rvar_uniform<unsigned int> r2(&p2, 0, 10);
    alg_obj.push_back(fact.get<op_xo_npoint>(&r2, 1));
   
    // 10% probability of applying a mutation in [0.0,1.0]
    prng_kiss p3;
    prng_kiss p4;
    rvar_normal<double> r_vals(&p3, 0.0, 1.0);
    rvar_uniform<double> r_probs(&p4, 0.0, 1.0);
    alg_obj.push_back(fact.get<op_mut_offset>(&r_vals, &r_probs, 0.1));

    // Fitness function.
    alg_obj.push_back(point_spread);

    alg_obj.push_back(fact.get<op_term_fixed_time>(milliseconds(300)));
    
    alg_obj.run();

    // Print out the population.
    alg_obj.clear();
    alg_obj.push_back(fact.get<print>(10));
    alg_obj.run_once();

    return false;
}
