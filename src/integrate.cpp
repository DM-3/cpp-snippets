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
    // function to be integrated
    auto f = [](double x) { return exp(-x*x); };

    // numerically approximate integral on range [-5, 5]
    // with trapezoidal rule on 100 sections
    auto I = integrate<double>(f, -5.0, 5.0, 100);

    // print result
    std::cout << "approximate integral: " << I << std::endl;

    return 0;
}
