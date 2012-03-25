#include <iostream>
#include <chrono>

#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_term_fixed_time()
{
    const int num_msec = 100;
    const double pass = 0.001;
    using std::chrono::microseconds;
    using std::chrono::milliseconds;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;

    alg<std::vector, std::list, float> alg_obj(16,6);

    prng_kiss prng1;
    rvar_uniform<float> r1(&prng1, -2.0, 2.0);
    alg_obj.make_push_back<op_init_rand>(&r1);

    milliseconds ttl(num_msec);
    alg_obj.make_push_back<op_term_fixed_time>(ttl);

    auto start = high_resolution_clock::now();
    alg_obj.run();
    auto end = high_resolution_clock::now() - start;

    std::cout << " | Run time was ";
    std::cout << duration_cast<microseconds>(end).count();
    std::cout << "us compared to a set time of ";
    std::cout << num_msec*1000 << "us." << std::endl;

    bool test_failed = false;
    int delta_t = duration_cast<milliseconds>(end).count() - num_msec;
    if(std::abs(delta_t) > pass*num_msec)
    {
        test_failed = true;
    }

    return test_failed;
}
