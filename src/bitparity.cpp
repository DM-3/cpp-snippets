#include <inttypes.h>
#include <bitset>
#include <iostream>



inline size_t bitparity_iterative(uint64_t n)
{
    while (n > 1)
        n = (n & 1UL) ^ (n >> 1);
        
    return n;
}


inline size_t bitparity_parallel_xor(uint64_t n)
{
    n ^= (n >> 32);
    n ^= (n >> 16);
    n ^= (n >> 8);
    n ^= (n >> 4);
    n ^= (n >> 2);
    n ^= (n >> 1);

    return n & 1UL;    
}


inline size_t bitparity_mul(uint64_t n)
{
    const uint64_t h1 = 0x8888'8888'8888'8888;
    const uint64_t h2 = 0x1111'1111'1111'1111;

    n ^= (n << 1);
    n ^= (n << 2);
    n = (n & h1) * h2;

    return n >> 63;
}


inline size_t bitparity_bitset(const uint64_t n)
{
    return std::bitset<64>(n).count() & 1;
}


#ifdef __GNUG__

inline size_t bitparity_builtin(const uint64_t n)
{
    return __builtin_parityll(n);
}

#endif



int main()
{
    // prepare random bit sequence
    std::srand(time(nullptr));
    uint64_t n = (uint64_t(std::rand()) << 32) | std::rand();

    std::cout << "n: " << std::bitset<64>(n) << std::endl;

    // print bitparity results
    std::cout << "bitparity naive: "        << bitparity_iterative(n)    << std::endl;
    std::cout << "bitparity parallel xor: " << bitparity_parallel_xor(n) << std::endl;
    std::cout << "bitparity multiply: "     << bitparity_mul(n)          << std::endl;
    std::cout << "bitparity bitset: "       << bitparity_bitset(n)       << std::endl;
#ifdef __GNUG__
    std::cout << "bitparity builtin: "      << bitparity_builtin(n)      << std::endl;
#endif

    return 0;
}
