#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_xo_npoint()
{
	obj_fact<std::vector, std::vector, int> fact;
    auto alg_obj = fact.get<alg>(8,12);

    auto printer = fact.get<print>(5);

    alg_obj.push_back(fact.get<op_init_debug>());
    alg_obj.push_back(printer);
    alg_obj.push_back(fact.get<op_sel_trunc>(0.5));
    alg_obj.push_back(printer);

    prng_kiss p;
    rvar_uniform<unsigned int> xop_src(&p, 0, 12);
    alg_obj.push_back(fact.get<op_xo_npoint>(&xop_src, 3));
    alg_obj.push_back(printer);

    alg_obj.run_once();
    bool test_failed = true;
    /*
    // Check results.
    for(uint32_t i = 0; i < p.size(); ++i)
    {
        // All genomes should be unavailable.
        if(p[i].avail != false)
        {
            DEBUG_OUT("Genome available.");
            test_failed = true;
        }

        if(i == 0 || i == 1)
        {
            // Parent
            // Parents should have their fitness unchanged.
            if(p[i].fitness != 0.0)
            {
                DEBUG_OUT("Parent fitness changed.");
                test_failed = true;
            }
        }
        else
        {
            // Child
            // Children should have evald set false.
            if(p[i].evald != false)
            {
                DEBUG_OUT("Child marked as evald.");
                test_failed = true;
            }

            for(uint32_t j = 0; j < p[i].size(); ++j)
            {
                // Els 0-3 should be from genome 0.
                // Els 4-5 should be from genome 1.
                // Els 6-10 should be from genome 0.
                // Els 11-18 should be from genome 1.
                // Els 19-23 should be from genome 0.
                if(j < 4 || (j >= 6 && j < 11) || (j >= 19 && j < 24))
                {
                    // genome 0
                    if(p[i][j] != p[0][j])
                    {
                        std::cout << "Data mismatch: " << p[i][j] << " != " << p[1][j] << std::endl;
                        test_failed = true;
                    }
                }
                else
                {
                    // genome 1
                    if(p[i][j] != p[1][j])
                    {
                        std::cout << "Data mismatch: " << p[i][j] << " != " << p[0][j] << std::endl;
                        test_failed = true;
                    }
                }
            }
        }
    }
    */

	return test_failed;
}
