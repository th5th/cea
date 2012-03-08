// Population DS
#ifndef CEA_POP_H
#define CEA_POP_H

template <typename T>
class Pop
{
    public:
        Pop(int p_s, int g_s)
        {
            pop.resize(p_s);
            typename std::vector< Genome<T> >::iterator it;
            for(it = pop.begin(); it != pop.end(); ++it)
                it->resize(g_s);
        }

        unsigned int size() { return pop.size(); };
        void resize(unsigned int size) { pop.resize(size); };
        typename std::vector< Genome<T> >::iterator begin() { return pop.begin(); };
        typename std::vector< Genome<T> >::iterator end() { return pop.end(); };
        // May want to add direct random access - []?

    private:
        std::vector< Genome<T> > pop;
};

#endif // CEA_POP_H
