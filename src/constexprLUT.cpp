#include <iostream>
#include <array>
#include <functional>



template<typename T, size_t N>
constexpr std::array<T, N> generateLUT(std::function<T (size_t)> func)
{
    auto arr = std::array<T, N>();
    for (size_t i = 0; i < N; i++)
        arr[i] = func(i);
    return arr;
}



int main()
{
    // function used to generate lookup table entries from indices
    auto fnGen = [](size_t i) -> double
        { 
            return 1.0 / (i + 1); 
        };

    // number of elements
    const size_t SIZE = 100;

    // generate lookup table using generator function
    const auto LUT = generateLUT<double, SIZE>(fnGen);

    // print entries
    for (size_t i = 0; i < SIZE; i++)
        std::cout << i << ": \t" << LUT[i] << "\n";
    std::cout << std::endl;

    return 0;
}
