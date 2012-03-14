#include <iostream>
#include <Cea/Core>

using namespace cea;

double test_f(Genome<uint32_t> const& g)
{
    double retval = 0;
    for(uint32_t i = 0; i < g.size(); ++i)
    {
        retval += static_cast<double>(g[i]);
    }
    return retval;
}

bool test_evalfitness()
{
    Pop<uint32_t> p(10, 1);
    std::vector<uint32_t> f_vals(p.size(), 0);

    for(uint32_t i = 0; i < p.size(); ++i)
    {
        for(uint32_t j = 0; j < p[i].size(); ++j)
        {
            f_vals[i] += i*j;
            p[i][j] = i*j;
        }
    }

    OpEvalFitness<uint32_t> evaluator(test_f);
    evaluator.apply_to(p);

    bool test_failed = false;

    for(uint32_t i = 0; i < p.size(); ++i)
    {
        if(p[i].fitness != f_vals[i] || p[i].avail != true || p[i].evald != true)
        {
           test_failed = true;
        }
        else
        {
           test_failed = false;
        }
    }
    return test_failed;
}
