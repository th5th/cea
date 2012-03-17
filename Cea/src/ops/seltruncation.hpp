// Simple truncation selection algorithm.
// Selects strongest P% of the population  and
// marks them as available.
// TODO Investigation of manual optimisation vs. STL.
#ifndef CEA_SELTRUNCATION_HPP
#define CEA_SELTRUNCATION_HPP

template <typename T>
class OpSelTruncation : public OpPop<T>
{
    public:
        OpSelTruncation(double pc)
        {
            if(pc < 0.0 || pc > 1.0)
            {
                throw(std::invalid_argument("Selection rate must be in [0,1] in OpSelTruncation."));
            }
            else
            {
                sel_pc = pc;
            }
        }

        void apply_to(Pop<T>& p)
        {
            unsigned int k = std::floor(((1.0 - sel_pc) * p.size()) + 0.5);
            // STL solution.
            std::nth_element(p.begin(), p.begin()+k, p.end());
            std::for_each(p.begin(), p.begin()+k, [](Genome<T>& g){ g.fitness = 0.0; g.evald = false; g.avail = true; });
        }

    private:
        double sel_pc;
};

#endif // CEA_SELTRUNCATION_HPP
