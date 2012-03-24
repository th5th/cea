#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_mut_offset()
{
    alg<std::vector, std::list, float> alg(10,10);
    auto printer = alg.make_op<print>(6);

    alg.make_and_push_back<op_init_debug>();
    alg.push_back(printer);

    prng_kiss pv(231001351367LL), pp(6123432556721LL);
    rvar_normal<float> rv(&pv, 0.0, 0.1);
    rvar_uniform<double> rp(&pp, 0.0, 1.0);
    alg.make_and_push_back<op_mut_offset>(&rv,&rp,0.1);
    alg.push_back(printer);

    alg.run_once();

    return true;
}
