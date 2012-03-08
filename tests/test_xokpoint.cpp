#include <Cea/Core>
#include <Cea/Operators>
#include <Cea/Random>

using namespace cea;

bool test_xokpoint()
{
    bool test_failed = false;
	Pop<uint64_t> p(4,24);

    // Mock initalisation.
    for(uint64_t i = 0; i < p.size(); ++i)
    {
        p[i].set_avail(false);
        p[i].set_evald(false);
        p[i].set_fitness(0.0);
        for(uint64_t j = 0; j < p[i].size(); ++j)
        {
            p[i][j] = 24*i + j;
        }
    }

    // Mock selection.
	p[2].set_avail(true);
	p[3].set_avail(true);

    uint64_t pts[] = {0,0,11,6,11,4,0,19};
    // In generating the crossover points, gen_
    // and check_points should reduce this set
    // down to 4,6,11,19.
    std::vector<uint64_t> points(pts, pts+8);
    DebugRVar<uint64_t> xo_points(points);
	OpXoKpoint<uint64_t, 2, 4> xo(&xo_points);
	xo.apply_to(p);

    // Check results.
    for(uint32_t i = 0; i < p.size(); ++i)
    {
        // All genomes should be unavailable.
        if(p[i].is_avail() != false)
        {
            DEBUG_OUT("Genome available.");
            test_failed = true;
        }

        if(i == 0 || i == 1)
        {
            // Parent
            // Parents should have their fitness unchanged.
            if(p[i].get_fitness() != 0.0)
            {
                DEBUG_OUT("Parent fitness changed.");
                test_failed = true;
            }
        }
        else
        {
            // Child
            // Children should have evald set false.
            if(p[i].is_evald() != false)
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

	return test_failed;
}
