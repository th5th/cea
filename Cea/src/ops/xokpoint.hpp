// Fully templated edition.
// TODO Allow variable number of children independent of parents.
// TODO Possibly remove integer template parameters. Value?
#ifndef CEA_XOKPOINT_HPP
#define CEA_XOKPOINT_HPP

template <typename T, int N_PAR, int N_XOP>
class OpXoKpoint : public OpPop<T>
{
    public:
        // Constructors
        OpXoKpoint(RVar<uint64_t> * src)
            : source(src) {}

        void apply_to(Pop<T>& p)
        {
            std::vector<uint64_t> xo_points;
            // Parents are guaranteed unchanged later.
            std::deque< Genome<T> const* > pa;
            std::deque< Genome<T>* > ch;

            // Separate unavailable and available genomes.
            s = p[0].size();
            for(uint64_t i = 0; i < p.size(); ++i)
            {
                if(p[i].avail == true)
                {
                    ch.push_back(&p[i]);
                }
                else
                {
                    pa.push_back(&p[i]);
                }
            }

            // While sufficient genomes then conduct crossover.
            while(ch.size() >= N_PAR && pa.size() >= N_PAR)
            {
                gen_points(xo_points);
                do_xo(xo_points, pa, ch);
            }

            // Check for leftovers!
            if(pa.size() != 0 || ch.size() != 0)
            {
                // Do something useful.
                DEBUG_OUT("Population size not compatible with this operator's settings!");
            }
        }

    private:
        // Genome length shortcut.
        uint64_t s;
        RVar<uint64_t> * source;

        // Helper functions.
        void check_points(std::vector<uint64_t>& points)
        {
            // Sort and cull repeated els.
            std::sort(points.begin(), points.end());
            points.resize(std::unique(points.begin(), points.end()) - points.begin());

            while(points.size() != N_XOP+2)
            {
                // Top up points.
                while(points.size() < N_XOP+2)
                {
                    points.push_back(source->rand() % s);
                }
                // Sort and cull repeated els.
                std::sort(points.begin(), points.end());
                points.resize(std::unique(points.begin(), points.end()) - points.begin());
            }

            return;
        }

        void gen_points(std::vector<uint64_t>& points)
        {
            // Generate some crossover points.
            if(points.size() != 0)
            {
                points.clear();
            }
            points.resize(N_XOP+2, 0);

            for(uint64_t i = 1; i < N_XOP+1; ++i)
            {
                points[i] = source->rand() % s;
            }

            points[N_XOP+1] = s;

            // Remove duplicates and top up.
            check_points(points);

            return;
        }

        void do_xo(std::vector<uint64_t> points, std::deque< Genome<T> const* >& p, std::deque< Genome<T>* >& c)
        {
            // Copy over genes according to vector points.
            for(uint64_t i = 0; i < N_PAR; ++i)
            {
                for(uint64_t j = i+1; j < points.size(); j += N_PAR)
                {
                    std::copy(p[0]->begin() + points[j-1], p[0]->begin() + points[j], c[0]->begin() + points[j-1]);
                }
                // Pop each parent as we are done with their precious genes.
                p.pop_front();
            }

            // Polish c[0]'s members (lol) and copy to c[1].
            c[0]->avail= false; c[0]->evald = false; c[0]->fitness = 0.0;
            for(uint64_t i = 1; i < N_PAR; ++i)
            {
                *c[1] = *c[0];
                c.pop_front();
            }

            // Pop last child pointer - doesn't need to copied on.
            c.pop_front();

            return;
        }
};

#endif // CEA_OPXOKPOINT_HPP
