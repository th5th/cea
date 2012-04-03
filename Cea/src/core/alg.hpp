// Central algorithm class
#ifndef CEA_ALG_HPP
#define CEA_ALG_HPP

namespace alg_internal
{
    using std::chrono::duration;
    using std::chrono::high_resolution_clock;
    using std::chrono::nanoseconds;
    using std::chrono::time_point;

    // Exponential smoothing factor for times.
    const double ALPHA = 0.1;

    template <template <typename,typename> class COuter,
             template <typename,typename> class CInner,
             typename T>
    class alg
    {
        public:
            typedef typename std::function<void(pop<COuter,CInner,T>&)>
                op_type;

            alg(int p_s, int g_s) : p(p_s, g_s)
            {
                operations.reserve(10);
            }

            alg(int p_s, int g_s, std::vector<op_type> ops)
                : operations(ops), p(p_s, g_s) { }

            void push_back(op_type op) { operations.push_back(op); }
            void pop_back() { operations.pop_back(); }

            void clear() { operations.clear(); }

            // Run operation loop once.
            inline void run_once()
            {
                times.resize(operations.size());
                time_point<high_resolution_clock> start;

                auto op_it = operations.begin();
                for(int i = 0; op_it != operations.end(); ++op_it, ++i)
                {
                    start = high_resolution_clock::now();
                    (*op_it)(p);
                    nanoseconds delta_t = high_resolution_clock::now() - start;

                    uint64_t smooth_num_ticks = static_cast<uint64_t>(
                            std::round(ALPHA*delta_t.count()));
                    smooth_num_ticks += static_cast<uint64_t>(
                            std::round((1-ALPHA)*times[i].count()));
                    times[i] = nanoseconds(smooth_num_ticks);
                }
            }

            // Run operation loop until p.running() is set false be loop body.
            void run()
            {
                p.running(true);
                while(p.running())
                {
                    run_once();
                    // Output times etc.
                }
            }

        private:
            std::vector<nanoseconds> times;

            std::vector<op_type> operations;

            pop<COuter,CInner,T> p;
    };
}

using alg_internal::alg;

#endif // CEA_ALG_HPP
