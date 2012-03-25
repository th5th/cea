/*
 * Factory class to template-instantiate cea-objects and
 * call their constructors, returning an instance. Any
 * objects requiring 3 template parameters (two STL-like
 * containers COuter and CInner, and a gene type T) can
 * be made. Generally these objects will be alg or op_*
 * instances.
 * 
 * Example: 
 *
 * cea::obj_fact<std::vector, std::vector, char> fact;
 * auto alg = fact.get<cea::alg>(p_s = 128, g_s = 16);
 * alg.push_back(fact.get<cea::op_init_rand>(...));
 */

#ifndef CEA_OBJ_FACT_HPP
#define CEA_OBJ_FACT_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class obj_fact
{
    public:
        template <template 
        <template <class U1, class U2 = std::allocator<U1> > class _COuter,
        template <class V1, class V2 = std::allocator<V1> > class _CInner,
        typename _T> class OpClass,
        typename ...ArgTypes>
        OpClass<COuter,CInner,T> get(ArgTypes ...args)
        {
            OpClass<COuter,CInner,T> inst(args...);
            return inst;
        }
};

#endif // CEA_OBJ_FACT_HPP
