#include <iostream>

#include <Cea/Core>
#include <Cea/Random>

// Kolmogorov-Smirnov test.
// Tests whether data generated by a provided 
// cea::RVar is likely to have come from a
// distribution whose CDF is provided.
#include "kstest.hpp"

using namespace cea;

bool test_rvaruniform()
{
    const int n_tests = 1000; const double alpha = 0.05;
    const double a = -3.1; const double b = 1.7;
    PrngMLCGXORShift p;
    try
    {
        RVarUniform<double> ru(&p,b,b);
    }
    catch(std::exception& e)
    {
        std::cout << " | Caught exception: " << e.what() << std::endl;
    }
    RVarUniform<double> ru(&p,a,b);
    std::function<double(double)> cdf = [a,b](double x){ return (x-a)/(b-a); };
    KSTest tester(&ru, cdf, 100);
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
