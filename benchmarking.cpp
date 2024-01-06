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
    /*
    FUNC(Leet::lengthOfLongestSubstring1::solution),
    FUNC(Leet::lengthOfLongestSubstring2::solution),
    FUNC(Leet::lengthOfLongestSubstring3::solution),
    */
    FUNC(Leet::longestValidParentheses::solution1),
    FUNC(Leet::longestValidParentheses::solution2),
    FUNC(Leet::longestValidParentheses::solution3)
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

    std::cout << "making test data... " << std::endl;
    for(size_t k = 0; k < strVec.size(); ++k) {
        strVec[k] = Benchmarking::makeRandomString(strlen, "((((((()))))))");
    }
    
    for (size_t idx = 0; idx < sizeof(funcTable)/sizeof(funcTable[0]); ++idx)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "running benchmark for " << funcTable[idx].name << std::endl;

        const int warmUpIterations = 18;
        std::cout << "warming up for "<< warmUpIterations << " iterations ..." << std::endl;
        // Warm-up phase
        for (int i = 0; i < warmUpIterations && i < strVec.size(); ++i) {
            volatile auto result = funcTable[idx].func(strVec[i]);
            (void)result; // Prevents the compiler from optimizing away the call
        }

        std::cout << "testing for " << strVec.size() << " test cases ..." << std::endl;
        std::vector<long> resultVec;
        resultVec.resize(strVec.size());
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t k = 0 ; k < strVec.size(); ++k)
        {
            resultVec[k] = funcTable[idx].func(strVec[k]);
        } 

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        long sum=0;//, max, min, std;
        for (size_t k = 0; k < resultVec.size(); k++) {
            sum += resultVec[k];
        }

        std::cout << "result sum: " << sum << std::endl;
        std::cout << "time: " <<  duration/1000.0 << "ms " << std::endl;
        std::cout << "iterations: " << iterations << ", at " << (1000 * duration) / iterations 
            << "ns per iteration" << std::endl;
    }
    return 0;
}
