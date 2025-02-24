#include <iostream>



constexpr unsigned long int factorial(unsigned int n)
{
    return n > 1 ? n * factorial(n - 1) : 1;
}



int main()
{
    const auto n = 6;

    // const declared result will be computed at compile time
    const auto result = factorial(n);

    std::cout << "factorial of " << n << ": " << result << std::endl;

    return 0;
}
