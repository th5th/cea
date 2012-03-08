// Data structures.
#ifndef CEA_GENOME_H
#define CEA_GENOME_H

template <typename T>
class Genome
{
    public:
        Genome()
        {
            set_fitness(0.0);
            set_avail(true);
        }

        Genome(int size)
        {
            set_fitness(0.0);
            set_avail(true);
            genes.resize(size);
        }

        unsigned int size() { return genes.size(); };
        void resize(unsigned int size) { genes.resize(size); };
        typename std::vector<T>::iterator begin() { return genes.begin(); };
        typename std::vector<T>::iterator end() { return genes.end(); };

        double get_fitness() { return fitness; };
        void set_fitness(double f) { fitness = f; };
        bool is_avail() { return avail; };
        void set_avail(bool a) { avail = a; };

    private:
        double fitness;
        bool avail;
        std::vector<T> genes;
};

#endif // CEA_GENOME_H
