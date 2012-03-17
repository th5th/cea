// Data structures.
#ifndef CEA_GENOME_HPP
#define CEA_GENOME_HPP

template <typename T>
class Genome
{
    public:
        // TODO Add dependent [gs]etters for these fields to control state more closely.
        // Fitness measure, availability and evaluated flags.
        double fitness;
        bool avail;
        bool evald;

        Genome() :
            fitness(0.0), avail(true), evald(false) {}

        Genome(typename std::vector<T>::size_type g_s)
            : fitness(0.0), avail(true), evald(false), genes(g_s, 0) {}

        // Forward some of the underlying vector<T> functionality.
        typename std::vector<T>::size_type size() const { return genes.size(); }
        void resize(typename std::vector<T>::size_type size) { genes.resize(size); }
        typename std::vector<T>::iterator begin() { return genes.begin(); }
        typename std::vector<T>::const_iterator begin() const { return genes.begin(); }
        typename std::vector<T>::iterator end() { return genes.end(); }
        typename std::vector<T>::const_iterator end() const { return genes.end(); }

        // Random accessor operator.
        T& operator[](int i) { return genes[i]; }
        T const& operator[](int i) const { return genes[i]; }

        // Comparison and efficient swapping.
        bool operator<(Genome<T> const& g2) const { return fitness < g2.fitness; }
        friend void swap(Genome<T>&g1, Genome<T>& g2)
        {
            std::swap(g1.avail, g2.avail);
            std::swap(g1.evald, g2.evald);
            std::swap(g1.fitness, g2.fitness);
            g1.genes.swap(g2.genes);
            return;
        }

    private:
        std::vector<T> genes;
};

#endif // CEA_GENOME_HPP
