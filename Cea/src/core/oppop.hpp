// Operator classes.
#ifndef CEA_OPPOP_H
#define CEA_OPPOP_H

template <typename T>
class OpPop
{
    public:
        virtual void apply_to(Pop<T>& p) = 0;
};

#endif
