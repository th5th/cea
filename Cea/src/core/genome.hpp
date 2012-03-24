// Genome DS.
#ifndef CEA_GENOME_HPP
#define CEA_GENOME_HPP

template <template <class _U, class _V = std::allocator<_U> > class CInner,
         typename T>
class genome
{
    public:
        // Externalised typedefs of limited application...
        typedef typename CInner<T>::iterator iterator;
        typedef typename CInner<T>::const_iterator const_iterator;
        typedef typename CInner<T>::size_type size_type;

        genome() : alive_flag(false), evald_flag(false), f_val(0.0) { }

        genome(size_type g_s)
            : alive_flag(false), evald_flag(false),
            f_val(0.0), genes(g_s, static_cast<T>(0)) { }

        // Manipulators for genome's flags.
        bool alive() const { return alive_flag; }
        void alive(bool a)
        {
            // This logic changes evald_flag in the following cases.
            // new evald_flag | evald_flag | a | alive_flag
            //       0              1        0       1
            //       0              1        1       0
            evald_flag &= !(a^alive_flag);
            alive_flag = a; 
        }

        bool evald() const
        {
            if(alive_flag == true)
            {
                return evald_flag;
            }
            else
            {
                throw(std::runtime_error("In genome: alive_flag "
                    "must be true to read evald_flag."));
            }
        }

        void evald(bool e)
        {
            if(alive_flag == true)
            {
                evald_flag = e;
            }
            else
            {
                throw(std::runtime_error("In genome: alive_flag "
                   "must be true to write evald_flag."));
            }
        }

        double fitness() const
        {
            if(alive_flag == true && evald_flag == true)
            {
                return f_val;
            }
            else
            {
                throw(std::runtime_error("In genome: alive_flag &&"
                   " evald_flag must be true to read f_val."));
            }
        }

        void fitness(double f)
        {
            if(alive_flag == true && evald_flag == true)
            {
                f_val = f;
            }
            else
            {
                throw(std::runtime_error("In genome: alive_flag &&"
                   " evald_flag must be true to write f_val."));
            }
        }

        // Forward some of the underlying CInner<T> functionality.
        size_type size() const { return genes.size(); }

        void resize(size_type sz) { genes.resize(sz); }

        iterator begin() { return genes.begin(); }
        const_iterator begin() const { return genes.begin(); }

        iterator end() { return genes.end(); }
        const_iterator end() const { return genes.end(); }

        // Comparison and efficient swapping.
        bool operator<(genome<CInner,T> const& g2) const
        {
            return f_val < g2.f_val;
        }

        friend void swap(genome<CInner,T>& g1, genome<CInner,T>& g2)
        {
            std::swap(g1.alive_flag, g2.alive_flag);
            std::swap(g1.evald_flag, g2.evald_flag);
            std::swap(g1.f_val, g2.f_val);
            g1.genes.swap(g2.genes);
            return;
        }

    private:
        bool alive_flag;
        bool evald_flag;
        double f_val;

        CInner<T> genes;
};

#endif // CEA_GENOME_HPP
