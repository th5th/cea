// Base operator class.
#ifndef CEA_OPPOP_HPP
#define CEA_OPPOP_HPP

template <typename T>
class OpPop
{
    public:
        virtual void apply_to(Pop<T>& p) = 0;
};

#endif // CEA_OPPOP_HPP
