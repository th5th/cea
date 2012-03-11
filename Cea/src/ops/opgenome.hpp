// OpGenome shortcut class.
#ifndef CEA_OPGENOME_HPP
#define CEA_OPGENOME_HPP

template <typename T>
class OpGenome : public OpPop<T>
{
    public:
        void apply_to(Pop<T>& p)
        {
            for(uint64_t i = 0; i < p.size(); ++i)
            {
                apply_tog(p[i]);
            }
        }

    private:
        virtual void apply_tog(Genome<T>& g) = 0;
};

#endif // CEA_OPGENOME_HPP
