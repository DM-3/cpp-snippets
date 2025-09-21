#include <iostream>
#include <inttypes.h>
#include <random>



template<typename T>
void radixSort(T* arr, const size_t size)
{
    // iterations needed with given digits
    const size_t iterations = sizeof(T);
    
    // auxiliary array
    T* aux = new T[size];
    
    // buckets used for counting occurrences of a given digit
    size_t buckets[256];

    for (size_t it = 0; it < iterations; it++)
    {
        // reset buckets
        std::fill(buckets, buckets + 256, 0);

        // count digits
        for (size_t i = 0; i < size; i++)
        {
            uint8_t radix = ((uint8_t*)arr)[i * iterations + it];
            buckets[radix]++;
        }

        // compute offsets
        uint64_t sum = 0;
        for (size_t i = 0; i < 256; i++)
        {
            sum += buckets[i];
            buckets[i] = sum - buckets[i];
        }

        // reorder elements into auxiliary array
        for (size_t i = 0; i < size; i++)
        {
            uint8_t radix = ((uint8_t*)arr)[i * iterations + it];
            aux[buckets[radix]] = arr[i];
            buckets[radix]++;
        }

        // swap pointers to avoid copying
        std::swap(aux, arr);
    }

    // swap result if number of iterations is uneven
    // so the result is returned in the input array
    if (iterations & 1)
    {
        std::swap(aux, arr);
        std::copy(aux, aux + size, arr);
    }

    delete[] aux;
}



int main()
{
    // number of elements
    const size_t SIZE = 1e6;

    // prepare array of random elements
    auto array = new double[SIZE];

    for (size_t i = 0; i < SIZE; i++)
        array[i] = double(std::rand()) / RAND_MAX;

    // sort array
    radixSort(array, SIZE);

    // check array for ascending order
    bool sorted = true;
    for (size_t i = 1; i < SIZE && sorted; i++)
        sorted = array[i] >= array[i - 1];
    std::cout << "sorted: " << (sorted ? "true" : "false") << std::endl;

    delete[] array;
}
