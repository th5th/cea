#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_initrand()
{
    bool test_failed = false;
    Pop<float> p(4,24);
    PrngKISS prng1, prng2;
    RVarUniform<float> r(&prng1, -2.0, 2.0);

    // Get benchmark data.
    std::vector<float> benchmark(96,0);
    for(uint64_t i = 0; i < 96; ++i)
    {
        benchmark[i] = r.rand();
    }

    r.set_source(&prng2);
    OpInitRand<float> init(&r);
    init.apply_to(p);

    // Check result.
    for(uint64_t i = 0; i < p.size(); ++i)
    {
        // avail should be false.
        if(p[i].avail != false)
        {
            DEBUG_OUT("Avail is set.");
            test_failed = true;
        }

        // evald should be false.
        if(p[i].evald != false)
        {
            DEBUG_OUT("Evald is set.");
            test_failed = true;
        }

        // fitness should be 0.0.
        if(p[i].fitness != 0.0)
        {
            DEBUG_OUT("Fitness not set to 0.0.");
            test_failed = true;
        }

        for(uint64_t j = 0; j < p[i].size(); ++j)
        {
            // Check data against benchmark.
            if(p[i][j] != benchmark[24*i + j])
            {
                test_failed = true;
            }
        }
    }

    return test_failed;
}
