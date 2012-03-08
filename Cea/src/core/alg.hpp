// Central algorithm class
#ifndef CEA_ALG_H
#define CEA_ALG_H

template <typename T>
class Cea
{
    public:
        Cea();
        Cea(int n_i, int n_g);
        Cea(int n_i, int n_g, std::vector< OpPop<T>* > ops);
        ~Cea();

        int get_pop_size();
        void set_pop_size(int p_s);

        int get_gno_size();
        void set_gno_size(int g_s);

        void add_op(OpPop<T>* op);
        void rm_last_op();
        void clear_pops();

        // Functions to set up output... Yawn.

        // The Big One.
        void run();

    private:
        std::vector< OpPop<T>* > operations;
        Pop<T> p;
};

#endif // CEA_ALG_H
