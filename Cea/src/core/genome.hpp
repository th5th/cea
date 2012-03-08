// Data structures.
#ifndef CEA_GENOME_HPP
#define CEA_GENOME_HPP

template <typename T>
class Genome
{
    public:
        Genome()
        {
            set_fitness(0.0);
            set_avail(true);
            set_evald(false);
        }

        Genome(int g_s) : genes(g_s, 0)
        {
            set_fitness(0.0);
            set_avail(true);
            set_evald(false);
        }

        // Forward some of the underlying vector<T> functionality.
        // TODO
        // change to size_type?
        // change return type to const?
        unsigned int size() const { return genes.size(); }
        void resize(unsigned int size) { genes.resize(size); }
        typename std::vector<T>::iterator begin() { return genes.begin(); }
        typename std::vector<T>::const_iterator begin() const { return genes.begin(); }
        typename std::vector<T>::iterator end() { return genes.end(); }
        typename std::vector<T>::const_iterator end() const { return genes.end(); }

        // Random accessor operator.
        T& operator[](int i) { return *(genes.begin() + i); }
        T const& operator[](int i) const { return *(genes.begin() + i); }

        double get_fitness() const { return fitness; }
        void set_fitness(double f) { fitness = f; }
        bool is_avail() const { return avail; }
        void set_avail(bool a) { avail = a; }
        bool is_evald() const { return evald; }
        void set_evald(bool e) { evald = e; }

    private:
        double fitness;
        bool avail;
        bool evald;
        std::vector<T> genes;
};

#endif // CEA_GENOME_HPP
