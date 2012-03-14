// Simple truncation selection algorithm.
// Marks weakest P% of the population as available.
// TODO Investigation of manual optimisation vs. STL.
#ifndef CEA_SELTRUNCATION_HPP
#define CEA_SELTRUNCATION_HPP

template <typename T>
class OpSelTruncation : public OpPop<T>
{
    public:
        OpSelTruncation(double pc)
            : sel_pc(pc) {}

        void apply_to(Pop<T>& p)
        {
            unsigned int k = std::floor((sel_pc * p.size()) + 0.5);
            // STL solution.
            std::nth_element(p.begin(), p.begin()+k, p.end());
            std::for_each(p.begin(), p.begin()+k, [](Genome<T>& g){ g.fitness = 0.0; g.evald = false; g.avail = true; });
        }

    private:
        double sel_pc;
};

#endif // CEA_SELTRUNCATION_HPP
