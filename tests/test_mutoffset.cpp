#include <iostream>
#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

template <typename T>
void print_pop(Pop<T> const& p)
{
    for(unsigned int i = 0; i < p.size(); ++i)
    {
        for(unsigned int j = 0; j < p[i].size(); ++j)
        {
            std::cout << p[i][j] << " ";
        }
        std::cout << " | avail = " << p[i].avail;
        std::cout << ", evald = " << p[i].evald;
        std::cout << ", fitness = " << p[i].fitness;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool test_mutoffset()
{

    Pop<double> p(10,10);

    for(unsigned int i = 0; i < p.size(); ++i)
    {
        for(unsigned int j = 0; j < p[i].size(); ++j)
        {
            p[i][j] = i*j;
        }
    }

    PrngKISS pm, pp;
    RVarNormal<double> rm(&pm, 0, 0.1);
    RVarUniform<float> rp(&pp, 0.0, 1.0);
    OpMutOffset<double, float> mutator(0.1, &rm, &rp);

    mutator.apply_to(p);

    print_pop<double>(p);
    return true;
}
