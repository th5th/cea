#include <iostream>
#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

// TODO Move print_pop into library - util/output.hpp?
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

bool test_seltruncation()
{
    double sel_p = 0.36;
    bool test_failed = false;
    Pop<float> p(13,10);
    // 13*0.36 gives 5 individuals to accept, 8 to reject.
    for(unsigned int i = 0; i < p.size(); ++i)
    {
        for(unsigned int j = 0; j < p[i].size(); ++j)
        {
            p[i][j] = i*j;
        }
        p[i].fitness = static_cast<double>(i);
        p[i].avail = false;
        p[i].evald = true;
    }

    try
    {
        OpSelTruncation<float> selector(-15.4);
    }
    catch(std::exception& e)
    {
        std::cout << " | Caught exception: " << e.what() << std::endl;
    }

    OpSelTruncation<float> selector(sel_p);

    selector.apply_to(p);

    for(unsigned int i = 0; i < p.size(); ++i)
    {
        if(p[i].evald == true && p[i].avail == false)
        {
            // survived.
            if(p[i].fitness < std::floor((1.0-sel_p)*p.size() + 0.5))
            {
                std::cout << "Found survivor with fitness less than the top " << sel_p*100 << "% of the population." << std::endl;
                test_failed = true;
            }
        }
        else if(p[i].evald == false && p[i].avail == true && p[i].fitness == 0.0)
        {
            // Culled.
        }
        else
        {
            std::cout << "Found genome with incompatible set of post-selection flags." << std::endl;
            test_failed = true;
        }
    }

    return test_failed;
}
