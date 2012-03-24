#include <iostream>
#include <chrono>

#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_term_fixed_time()
{
    const int ttl_usec = 100000;
    const double pass = 0.001;
    using std::chrono::microseconds;
    using std::chrono::milliseconds;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;

    alg<std::vector, std::list, float> alg_obj(16,6);

    prng_kiss prng1;
    rvar_uniform<float> r1(&prng1, -2.0, 2.0);
    alg_obj.make_and_push_back<op_init_rand>(&r1);

    microseconds ttl(ttl_usec);
    alg_obj.make_and_push_front<op_term_fixed_time>(duration_cast<milliseconds>(ttl));

    auto start = high_resolution_clock::now();
    alg_obj.run();
    auto end = high_resolution_clock::now() - start;

    std::cout << " | Run time was ";
    std::cout << duration_cast<microseconds>(end).count();
    std::cout << " compared to a set time of ";
    std::cout << ttl.count() << std::endl;

    bool test_failed = false;
    if(std::abs(duration_cast<microseconds>(end).count() - ttl.count())
        > pass*ttl_usec)
    {
        test_failed = true;
    }

    return test_failed;
}
