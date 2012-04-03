#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_mut_offset()
{
    obj_fact<std::vector, std::list, float> fact;
    auto alg_obj = fact.get<alg>(10,10);
    auto printer = fact.get<print>(6);

    alg_obj.push_back(fact.get<op_init_debug>());
    alg_obj.push_back(printer);

    prng_kiss pv(231001351367LL), pp(6123432556721LL);
    rvar_normal<float> rv(&pv, 0.0, 0.1);
    rvar_uniform<double> rp(&pp, 0.0, 1.0);
    alg_obj.push_back(fact.get<op_mut_offset>(&rv,&rp,0.1));
    alg_obj.push_back(printer);

    alg_obj.run_once();

    return true;
}
