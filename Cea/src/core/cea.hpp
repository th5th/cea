// Central algorithm class
#ifndef CEA_CEA_HPP
#define CEA_CEA_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class cea
{
    public:
        typedef typename std::function<void(pop<COuter,CInner,T>&)> op_type;

        cea(int p_s, int g_s)
            : operations(), p(p_s, g_s) { }
        cea(int p_s, int g_s, std::list<op_type> ops)
            : operations(ops), p(p_s, g_s) { }

        void op_list_push_back(op_type op) { operations.push_back(op); }
        void op_list_pop_back() { operations.pop_back(); }

        void op_list_push_front(op_type op) { operations.push_front(op); }
        void op_list_pop_front() { operations.pop_front(); }

        void op_list_clear() { operations.clear(); }

        // Functions to set up output go here.

        /*
         * op_type make(ArgTypes ...args)
         *
         * Helper member function to construct operator function objects
         * compatible with this instance of the cea class. Instantiates
         * a templated operator class OpClass with the previously provided
         * classes COuter, CInner and T.
         *
         * Can be used like:
         * cea_obj.op_push_back(cea_obj.make_op<op_class>(args,to,constructor);
         */
        template <template 
        <template <class U1, class U2 = std::allocator<U1> > class _COuter,
        template <class V1, class V2 = std::allocator<V1> > class _CInner,
        typename _T> class OpClass,
        typename ...ArgTypes>
        inline op_type make_op(ArgTypes ...args)
        {
            OpClass<COuter,CInner,T> inst(args...);
            return inst;
        }

        // Run loop.
        void run()
        {
            // (re)set population's running flag.
            p.running(true);
            auto op_it = operations.begin();
            while(p.running())
            {
                (*op_it)(p);
                if(++op_it == operations.end())
                {
                    op_it = operations.begin();
                }
                // do other things.
            }
        }

    private:
        std::list<op_type> operations;
        pop<COuter,CInner,T> p;
};

#endif // CEA_CEA_HPP
