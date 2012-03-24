#include <iostream>

#include <Cea/Core>
#include <Cea/Random>

// Kolmogorov-Smirnov test.
// Tests whether data generated by a provided 
// cea::RVar is likely to have come from a
// distribution whose CDF is provided.
#include "kstest.hpp"

using namespace cea;

class phi
{
    public:
        phi(double m, double s) : mu(m), sig(s) { }

        double operator()(double x)
        {
            return 0.5 * std::erfc(-0.707106781186547524 * (x-mu)/sig);
        }

    private:
        double mu, sig;
};

bool test_rvar_normal()
{
    const int num_tests = 1000; const double alpha = 0.05;
    const double mu = 0.0; const double sig = 1.0;

    prng_mlcg_xorshift p;
   
    try
    {
        rvar_normal<double> rn(&p,mu,0);
    }
    catch(std::exception& e)
    {
        std::cout << " | Caught exception: " << e.what() << std::endl;
    }

    rvar_normal<double> rn(&p,mu,sig);
    phi phi_obj(mu,sig);
    ks_test tester(&rn, phi_obj, 100);

    int num_successes = tester.n_tests(num_tests, alpha);

    std::cout << " | " << num_successes << " tests in ";
    std::cout << num_tests << " succeeded." << std::endl;

    bool test_failed;
    if(((1.0-alpha)*num_tests - num_successes) / num_tests < 0.05)
    {
        std::cout << " | This compares well with an expected"
           " pass count of " << (1.0-alpha)*num_tests << "." << std::endl;
        test_failed = false;
    }
    else
    {
        std::cout << " | This compares poorly with an expected"
           " pass count of " << (1.0-alpha)*num_tests << "." << std::endl;
        test_failed = true;
    }
    return test_failed;
}