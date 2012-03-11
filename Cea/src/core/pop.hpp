// Population DS
#ifndef CEA_POP_HPP
#define CEA_POP_HPP

template <typename T>
class Pop
{
    public:
        Pop(int p_s, int g_s)
            : pop(p_s, Genome<T>(g_s)) {}

        // Forward some of the underlying vector<T> functionality.
        typename std::vector<T>::size_type size() const { return pop.size(); }
        void resize(typename std::vector<T>::size_type size) { pop.resize(size); }
        typename std::vector< Genome<T> >::iterator begin() { return pop.begin(); }
        typename std::vector< Genome<T> >::const_iterator begin() const { return pop.begin(); }
        typename std::vector< Genome<T> >::iterator end() { return pop.end(); }
        typename std::vector< Genome<T> >::const_iterator end() const { return pop.end(); }

        // Random accessor operator.
        Genome<T>& operator[](int i) { return pop[i]; }
        Genome<T> const& operator[](int i) const { return pop[i]; }

    private:
        std::vector< Genome<T> > pop;
};

#endif // CEA_POP_HPP
