#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>
#include <math.h>

#include "benchmarking.hpp"
#include "leet.hpp"

// -------------------------------------------------------------------------------------------------

#define FUNC(f) {f, #f}

//typedef void (*funcptr)(void);

Benchmarking::FuncEntry<int, std::string> funcTable[] =
{
    FUNC(Leet::lengthOfLongestSubstring1::solution),
    FUNC(Leet::lengthOfLongestSubstring2::solution),
    FUNC(Leet::lengthOfLongestSubstring3::solution),
};

// -------------------------------------------------------------------------------------------------
int main()
{
    srand(time(0));

    std::vector<std::string> strVec;
    int iterations = 0;
    size_t strlen = 0;

    std::cout << "enter a number of test cases to run: ";
    std::cin >> iterations;
    std::cout << "enter string length per test case: ";
    std::cin >> strlen;
    
    strVec.resize(iterations);

    for(size_t k = 0; k < strVec.size(); ++k) {
        strVec[k] = Benchmarking::makeRandomString(strlen);
    }
    
    for (size_t idx = 0; idx < sizeof(funcTable)/sizeof(funcTable[0]); ++idx)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "running benchmark for " << funcTable[idx].name << std::endl;

        const int warmUpIterations = 10; // Or however many iterations you deem necessary

        // Warm-up phase
        for (int i = 0; i < warmUpIterations; ++i) {
            for (size_t k = 0; k < strVec.size(); ++k) {
                volatile auto result = funcTable[idx].func(strVec[k]);
                (void)result; // Prevents the compiler from optimizing away the call
            }
        }

        double result = 0;
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t k = 0 ; k < strVec.size(); ++k)
        {
            result += funcTable[idx].func(strVec[k]);
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
