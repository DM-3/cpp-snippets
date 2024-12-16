#include <inttypes.h>
#include <bitset>
#include <iostream>



inline size_t bitcount_parallel_add(uint64_t n)
{
    const uint64_t m1 = 0x5555'5555'5555'5555;     // 0b0101'0101'...
    const uint64_t m2 = 0x3333'3333'3333'3333;     // 0b0011'0011'...
    const uint64_t m4 = 0x0f0f'0f0f'0f0f'0f0f;     // 0b0000'1111'...

    n =  n       - ((n >> 1)  & 0x5555'5555'5555'5555);
    n = (n & m2) + ((n >> 2)  & 0x3333'3333'3333'3333);
    n = (n       +  (n >> 4)) & 0x0f0f'0f0f'0f0f'0f0f;
    n =  n       +  (n >> 8);
    n =  n       +  (n >> 16);

    return (n + (n >> 32)) & 0xff;
}


inline size_t bitcount_mul(uint64_t n)
{
    const uint64_t m1  = 0x5555'5555'5555'5555;     // 0b0101'0101'...
    const uint64_t m2  = 0x3333'3333'3333'3333;     // 0b0011'0011'...
    const uint64_t m4  = 0x0f0f'0f0f'0f0f'0f0f;     // 0b0000'1111'...
    const uint64_t h01 = 0x0101'0101'0101'0101;     // 0b0000'0001'...

    n =  n       - ((n >> 1)  & m1);
    n = (n & m2) + ((n >> 2)  & m2);
    n = (n       +  (n >> 4)) & m4;

    return (n * h01) >> 56;
}


inline size_t bitcount_bitset(const uint64_t n)
{
    return std::bitset<64>(n).count();
}


#ifdef __GNUG__

inline size_t bitcount_builtin(const uint64_t n)
{
    return __builtin_popcountll(n);
}

#endif


#ifdef __AVX__

#include <immintrin.h>

inline size_t bitcount_intrinsic(uint64_t n)
{
    return __popcntq(n);
}

#endif



int main()
{
    // prepare random bit sequence
    std::srand(time(nullptr));
    uint64_t n = (uint64_t(std::rand()) << 32) | std::rand();

    std::cout << "n: " << std::bitset<64>(n) << std::endl;

    // print bitcount results
    std::cout << "bitcount parallel add: "  << bitcount_parallel_add(n) << std::endl;
    std::cout << "bitcount multiply: "      << bitcount_mul(n)          << std::endl;
    std::cout << "bitcount bitset: "        << bitcount_bitset(n)       << std::endl;
#ifdef __GNUG__
    std::cout << "bitcount builtin: "       << bitcount_builtin(n)      << std::endl;
#endif
#ifdef __AVX__
    std::cout << "bitcount intrinsic: "     << bitcount_intrinsic(n)    << std::endl;
#endif

    return 0;
}
