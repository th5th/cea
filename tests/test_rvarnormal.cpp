#include <iostream>

#include <Cea/Core>
#include <Cea/Random>

// Kolmogorov-Smirnov test.
// Tests whether data generated by a provided 
// cea::RVar is likely to have come from a
// distribution whose CDF is provided.
#include "kstest.hpp"

using namespace cea;

bool test_rvarnormal()
{
    const int n_tests = 1000; const double alpha = 0.05;
    const double mu = 0.0; const double sig = 1.0;
    PrngMLCGXORShift p;
    try
    {
        RVarNormal<double> rn(&p,mu,0);
    }
    catch(std::exception& e)
    {
        std::cout << " | Caught exception: " << e.what() << std::endl;
    }
    RVarNormal<double> rn(&p,mu,sig);
    std::function<double(double)> phi = [mu,sig](double x){ return 0.5 * std::erfc(-0.707106781186547524 * (x-mu)/sig); };
    KSTest tester(&rn, phi, 100);
    int n_ss = tester.n_tests(n_tests, alpha) ;
    std::cout << " | " << n_ss << " tests in " << n_tests << " succeeded." << std::endl;
    bool test_failed;
    if(((1.0-alpha)*n_tests - n_ss) / n_tests < 0.05)
    {
        std::cout << " | This compares well with an expected pass count of " << (1.0-alpha)*n_tests << "." << std::endl;
        test_failed = false;
    }
    else
    {
        std::cout << " | This compares poorly with an expected pass count of " << (1.0-alpha)*n_tests << "." << std::endl;
        test_failed = true;
    }
    return test_failed;
}
