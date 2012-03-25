// Central algorithm class
#ifndef CEA_ALG_HPP
#define CEA_ALG_HPP

template <template <class U1, class U2 = std::allocator<U1> > class COuter,
         template <class V1, class V2 = std::allocator<V1> > class CInner,
         typename T>
class alg
{
    public:
        typedef typename std::function<void(pop<COuter,CInner,T>&)> op_type;

        alg(int p_s, int g_s)
            : operations(), p(p_s, g_s) { }
        alg(int p_s, int g_s, std::list<op_type> ops)
            : operations(ops), p(p_s, g_s) { }

        void push_back(op_type op) { operations.push_back(op); }
        void pop_back() { operations.pop_back(); }

        void push_front(op_type op) { operations.push_front(op); }
        void pop_front() { operations.pop_front(); }

        void clear() { operations.clear(); }

        // Useful shorthand for push_back(make_op<op_class>())
        template <template 
        <template <class U1, class U2 = std::allocator<U1> > class _COuter,
        template <class V1, class V2 = std::allocator<V1> > class _CInner,
        typename _T> class OpClass,
        typename ...ArgTypes>
        void make_and_push_back(ArgTypes ...args)
        {
            OpClass<COuter,CInner,T> inst(args...);
            operations.push_back(inst);
        }

        // Useful shorthand for push_front(make_op<op_class>())
        template <template 
        <template <class U1, class U2 = std::allocator<U1> > class _COuter,
        template <class V1, class V2 = std::allocator<V1> > class _CInner,
        typename _T> class OpClass,
        typename ...ArgTypes>
        void make_and_push_front(ArgTypes ...args)
        {
            OpClass<COuter,CInner,T> inst(args...);
            operations.push_front(inst);
        }

        /*
         * op_type make(ArgTypes ...args)
         *
         * Helper member function to construct operator function objects
         * compatible with this instance of the alg class. Instantiates
         * a templated operator class OpClass with the previously provided
         * classes COuter, CInner and T.
         *
         * Can be used like:
         * alg_obj.op_push_back(alg_obj.make_op<op_class>(args,to,constructor);
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

        // Run operation loop once.
        inline void run_once()
        {
            auto op_it = operations.begin();
            for(; op_it != operations.end(); ++op_it)
            {
                (*op_it)(p);
            }
        }

        // Run operation loop until p.running() is set false be loop body.
        void run()
        {
            // (re)set population's running flag.
            p.running(true);
            while(p.running())
            {
                run_once();
                // do other things?
            }
        }

    private:
        std::list<op_type> operations;
        pop<COuter,CInner,T> p;
};

#endif // CEA_ALG_HPP
