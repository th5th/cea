// OpGenome shortcut class.
#ifndef CEA_OPGENOME_H
#define CEA_OPGENOME_H

template <typename T>
class OpGenome : public OpPop<T>
{
    public:
        void apply_to(Pop<T>& p)
        {
            typename std::vector< Genome<T> >::iterator it;
            for(it = p.begin(); it != p.end(); ++it)
                apply_tog(*it);
        }

    private:
        virtual void apply_tog(Genome<T>& g) = 0;
};

#endif // CEA_OPGENOME_H
