#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>
#include <math.h>

// -------------------------------------------------------------------------------------------------
//#include "utils/Utils_FuncEntry.hpp"
#define FUNC(f) {f, #f}

//typedef void (*funcptr)(void);

namespace Utils
{

typedef long double TYPE;
typedef TYPE (*funcptr)(TYPE);

struct FuncEntry
{
    funcptr func;
    const char *name;
};

}

// -------------------------------------------------------------------------------------------------
#define INPUT_MAX 128

using Utils::TYPE;

TYPE fastInverseSquare(TYPE number);
TYPE inverseSquare(TYPE number);
TYPE socIdiot(TYPE number);
TYPE addMyselfToMyself(TYPE number);

Utils::FuncEntry funcTable[] =
{
    FUNC(fastInverseSquare),
    FUNC(inverseSquare),
    FUNC(addMyselfToMyself),
    FUNC(socIdiot)
};

TYPE fastInverseSquare(TYPE number)
{
    long i;
    TYPE x2, y;
    const TYPE threehalfs = 1.5f;

    x2 = number * 0.5f;
    y = number;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(TYPE*)&i;
    y = y * (threehalfs - (x2 * y * y));

    return y;
}

TYPE inverseSquare(TYPE number)
{
    return 1.0/sqrt(number);
}

TYPE addMyselfToMyself(TYPE number)
{
    return number + number * 8;
}

TYPE socIdiot(TYPE number)
{
    long i = *(long*)&number;
    number = i << 2;
    return number + (i << 3); 
}

TYPE function(int _iterations, const std::vector<TYPE> &arr, bool option = true)
{
    size_t idx;
    TYPE runningSum = 0.0; 

    if (option)
    {
        for (int j = 0; j < arr.size(); ++j)
        {
            runningSum += fastInverseSquare(arr[j]);
        }
    }
    else
    {
        for (int j = 0; j < arr.size(); ++j)
        {
            runningSum += 1.0/sqrt(arr[j]);
        }

    }

    return runningSum;
}

template <typename T>
void makeRandomArray(std::vector<T> &arr)
{
    for (int k = 0; k < arr.size(); ++k)
    {
        arr[k] = TYPE( (rand()) % INPUT_MAX + 1);
    }
    
    std::cout << "made random array: " << arr[0] << std::endl;
} 

void m2(std::vector<float> &arr)
{
    makeRandomArray(arr);
}

int main()
{
    srand(time(0));
    
    /**/
    //testing fn ptrs:
    void (*ptr)(std::vector<float> &);
    ptr = &m2;
    std::vector<float> test;
    test.resize(1244);
    ptr(test);

    std::cout << "ptr: " << (long*)&ptr << std::endl;

    std::vector<TYPE> arr;
    int iterations = 0;
    std::cout << "enter a number of iterations: ";
    std::cin >> iterations;
    
    arr.resize(iterations);

    for (size_t idx = 0; idx < sizeof(funcTable)/sizeof(funcTable[0]); ++idx)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "running benchmark for " << funcTable[idx].name << std::endl;
        makeRandomArray(arr);

        double result = 0;
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t k = 0 ; k < arr.size(); ++k)
        {
            result += funcTable[idx].func(arr[k]);
        } 

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
        std::cout << "result sum: " << result << std::endl;
        std::cout << "time: " <<  duration/1000.0 << "ms " << std::endl;
        std::cout << "iterations: " << iterations << ", at " << (1000 * duration) / iterations 
            << "ns per iteration" << std::endl;
    }
    return 0;
}
