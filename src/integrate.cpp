#include <iostream>
#include <functional>
#include <math.h>



template<typename T>
T integrate(std::function<T (T)> integrand, T begin, T end, size_t sections)
{
    T sum = (integrand(begin) + integrand(end)) / 2;

    for (size_t i = 1; i < sections; i++)
        sum += integrand(begin + i * (end - begin) / sections);

    return sum * (end - begin) / sections;
}



int main()
{
    /* approximate unit circle area */
    {
        // function to be integrated
        auto f = [](double x) { 
            return 2.0 * sqrt(1.0 - x*x); 
        };

        // numerically approximate integral on range [-1, 1]
        // with trapezoidal rule on 10000 sections
        auto I = integrate<double>(f, -1.0, 1.0, 10000);

        // print result
        std::cout << "approximate integral: " << I << std::endl;
    }

    /* approximate unit sphere volume */
    {
        // integrand for inner integral
        auto f = [](double x, double y) { 
            double radicand = 1.0 - x*x - y*y;
            return 2.0 * sqrt(radicand * (radicand >= 0));      // avoid nan with numerical errors
        };

        // integrand for outer integral
        auto f_outer = [&](double x) {
            auto fb = std::bind(f, x, std::placeholders::_1);
            double y_lim = sqrt(1.0 - x*x);
            return integrate<double>(fb, -y_lim, y_lim, 1000);  // integrate over y
        };

        auto I = integrate<double>(f_outer, -1.0, 1.0, 1000);   // integrate over x

        // print result
        std::cout << "approximate integral: " << I << std::endl;
    }

    return 0;
}
