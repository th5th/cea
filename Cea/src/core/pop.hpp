// Population DS
#ifndef CEA_POP_HPP
#define CEA_POP_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class pop
{
    public:
        typedef typename COuter< genome<CInner,T> >::pointer pointer;
        typedef typename COuter< genome<CInner,T> >::const_pointer
            const_pointer;
        typedef typename COuter< genome<CInner,T> >::iterator iterator;
        typedef typename COuter< genome<CInner,T> >::const_iterator
            const_iterator;
        typedef typename COuter< genome<CInner,T> >::size_type size_type;

        pop(int p_s, int g_s) :
            run_flag(true), genomes(p_s, genome<CInner,T>(g_s)) { }

        // Flag to allow termination of population.
        bool running() const { return run_flag; }
        void running(bool r) { run_flag = r; }

        // Forward some of the underlying vector<T> functionality.
        size_type size() const { return genomes.size(); }

        void resize(size_type size) { genomes.resize(size); }

        iterator begin() { return genomes.begin(); }
        const_iterator begin() const { return genomes.begin(); }

        iterator end() { return genomes.end(); }
        const_iterator end() const { return genomes.end(); }

    private:
        bool run_flag;
        COuter< genome<CInner,T> > genomes;
};

#endif // CEA_POP_HPP
