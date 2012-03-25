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

        alg(int p_s, int g_s) : p(p_s, g_s)
        {
            operations.reserve(10);
        }

        alg(int p_s, int g_s, std::vector<op_type> ops)
            : operations(ops), p(p_s, g_s) { }

        void push_back(op_type op) { operations.push_back(op); }
        void pop_back() { operations.pop_back(); }

        void clear() { operations.clear(); }

        // Useful shorthand for push_back(make_op<op_class>())
        template <template 
        <template <class U1, class U2 = std::allocator<U1> > class _COuter,
        template <class V1, class V2 = std::allocator<V1> > class _CInner,
        typename _T> class OpClass,
        typename ...ArgTypes>
        void make_push_back(ArgTypes ...args)
        {
            OpClass<COuter,CInner,T> inst(args...);
            operations.push_back(inst);
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
         * auto some_op = alg_obj.make<op_class>(args,to,constructor);
         * alg_obj.push_back(some_op);
         */
        template <template 
        <template <class U1, class U2 = std::allocator<U1> > class _COuter,
        template <class V1, class V2 = std::allocator<V1> > class _CInner,
        typename _T> class OpClass,
        typename ...ArgTypes>
        inline op_type make(ArgTypes ...args)
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
        std::vector<op_type> operations;
        pop<COuter,CInner,T> p;
};

#endif // CEA_ALG_HPP
