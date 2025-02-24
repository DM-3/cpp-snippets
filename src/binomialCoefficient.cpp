#include <iostream>



constexpr unsigned long int binomialCoefficient(unsigned int n, unsigned int k)
{
    if (k > n) 
        return 0;

    return k ? binomialCoefficient(n - 1, k - 1) * n / k : 1;
}



int main()
{
    const auto n = 49, k = 6;

    // const declared result will be computed at compile time
    const auto result = binomialCoefficient(n, k);

    std::cout << "binomial coefficient of (" << n << ", " << k << "): " 
        << result << std::endl;

    return 0;
}
