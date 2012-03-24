// Fixed time terminator, using <chrono>.
#ifndef CEA_TERM_FIXED_TIME_HPP
#define CEA_TERM_FIXED_TIME_HPP

namespace op_term_fixed_time_internal
{
    using std::chrono::milliseconds;
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::time_point;

    template <template <class U1, class U2 = std::allocator<U1> > class COuter,
             template <class V1, class V2 = std::allocator<V1> > class CInner,
             typename T>
    class op_term_fixed_time
    {
        public:
            op_term_fixed_time(milliseconds d) 
                : first_run(true), alg_duration(d) { }

            void operator()(pop<COuter,CInner,T>& p)
            {
                if(first_run == true)
                {
                    start = high_resolution_clock::now();
                    first_run = false;
                }

                auto t = high_resolution_clock::now() - start;
                if(duration_cast<milliseconds>(t) >= alg_duration)
                {
                    p.running(false);
                }
            }

        private:
            bool first_run;
            milliseconds alg_duration;
            time_point<high_resolution_clock> start;
    };
}           

using op_term_fixed_time_internal::op_term_fixed_time;
#endif // CEA_TERM_FIXED_TIME_HPP
