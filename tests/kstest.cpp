#include "kstest.hpp"

int ks_test::n_tests(int n, double alpha)
{
    int n_ss = 0;
    for(int i = 0; i < n; ++i)
    {
        if(single_test() > alpha)
        {
            ++n_ss;
        }
    }
    return n_ss;
}

double ks_test::single_test()
{
    // Returns significance level required for
    // the generated data's KS statistic to cause
    // rejection of H0, namely "the data is drawn
    // from the provided distribution".
    gen_data();
    double n = static_cast<double>(data.size());
    double D = 0.0, Di, dist, sample, sample_prev = 0.0;
    for(unsigned int i = 0; i < data.size(); ++i)
    {
        using std::max; using std::abs;
        sample = (i+1)/n;
        dist = cdf(data[i]);
        Di = max(abs(sample - dist), abs(sample_prev - dist));
        if(Di > D)
        {
            D = Di;
        }
        sample_prev = sample;
    }
    return 1.0 - ks_cdf(std::sqrt(n) * D);
}

void ks_test::gen_data()
{
    data.resize(n_points);
    for(int i = 0; i < n_points; ++i)
    {
        data[i] = gen->rand();
    }
    std::sort(data.begin(), data.end());
}


double ks_test::ks_cdf(double z)
{
    // CDF of the Kolmogorov-Smirnov distribution.
    using std::exp; using std::pow; using std::sqrt;
    if(z < 0.0)
    {
        throw("z must be non-negative in ks_cdf in ks_test.");
    }
    else if(z == 0.0)
    {
        return 0.0;
    }
    else if(z < 1.18)
    {
        double x = 1.23370055013616983/square(z);
        double y = exp(-x);
        return 2.25675833419102515*sqrt(x)*
            (y + pow(y,9) + pow(y,25) + pow(y,49));
    }
    else
    {
        double y = exp(-2.0*square(z));
        return 1.0 - 2.0*(y - pow(y,4) + pow(y,9));
    }
}
