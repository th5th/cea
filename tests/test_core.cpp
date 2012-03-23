#include <iostream>
#include <list>
#include <vector>
#include <Cea/Core>

using cea::pop;
using cea::print;

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class assign
{
    public:
        assign(T v) : asgn_val(v) { }

        void operator()(pop<COuter,CInner,T>& p)
        {
            auto p_it = p.begin();
            for(; p_it != p.end(); ++p_it)
            {
                auto it_gvf = p_it->begin();
                for(; it_gvf != p_it->end(); ++it_gvf)
                {
                    *it_gvf = asgn_val;
                }
            }
        }
    private:
        T asgn_val;
};

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class stopper
{
    public:
        void operator()(pop<COuter,CInner,T>& p)
        { 
            p.running(false);
        }
};

bool test_core()
{
    cea::cea<std::vector, std::list, char> alg(12,6);

    alg.op_list_push_back(alg.make_op<assign>('x'));
    alg.op_list_push_back(alg.make_op<print>());
    alg.op_list_push_back(alg.make_op<stopper>());
    std::cout << "run once..." << std::endl;
    alg.run();

    alg.op_list_pop_front();
    alg.op_list_push_front(alg.make_op<assign>('o'));
    std::cout << "run twice..." << std::endl;
    alg.run();

    return 0;
}
