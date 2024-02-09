#include <iostream>
#include <chrono>
#include <array>
#include <vector>
#include <algorithm>
#include <math.h>
#include <type_traits>

#include "benchmarking.hpp"
#include "leet.hpp"

// -------------------------------------------------------------------------------------------------

#define FUNC(f) {f, #f}
using RET_TYPE = int; //std::vector< std::vector<int> >;
using ARG_TYPE = std::string; //std::vector<int>&;
//typedef void (*funcptr)(void);

Benchmarking::FuncEntry<RET_TYPE, ARG_TYPE> funcTable[] =
{
    //<int, std::string>
    /*
    FUNC(Leet::lengthOfLongestSubstring::solution1),
    FUNC(Leet::lengthOfLongestSubstring::solution2),
    FUNC(Leet::lengthOfLongestSubstring::solution3),
    */
    
    FUNC(Leet::longestValidParentheses::solution1),
    FUNC(Leet::longestValidParentheses::solution2),
    FUNC(Leet::longestValidParentheses::solution3)
    

    //<std::vector< std::vector<int> >, std::vector<int>&>
    // FUNC(Leet::findMatrix::solution1),
    // FUNC(Leet::findMatrix::solution2)
};

template<typename T>
T generateRandomValue(size_t len) {
    if constexpr (std::is_same<T, std::string>::value) {
        std::string str;
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> char_dist(0, 26);
        const char charset[] = "((((((((((((()))))))))))))";
            //"abcdefghijklmnopqrstuvwxyz";
        std::generate_n(std::back_inserter(str), len, [&]() { return charset[char_dist(generator)]; });
        return str;
    } else if constexpr (std::is_same<T, std::vector<int>>::value) {
        std::vector<int> vec;
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<> num_dist(1, INT_MAX);
        std::generate_n(std::back_inserter(vec), len, [&]() { return num_dist(generator); });
        return vec;
    } else {
        //handle unsupported type
        return T{};
    }
}

template<typename T>
int handleResult(const T& result)
{
    int returnValue = 0;
    if constexpr(std::is_same<T, std::string>::value) 
    {
        std::cout << "handling std::string result" << std::endl;
        returnValue = result.size();
    }
    else if constexpr(std::is_same<T, std::vector<int>>::value) 
    {
        std::cout << "handling std::vector<int> result" << std::endl;

        for (int k : result) 
        {
            returnValue += k;
        }
    }
    else if constexpr(std::is_same<T, int>::value) 
    {
        std::cout << "handling int result " << std::endl;
        returnValue = result;
    }
    return returnValue;
}


// -------------------------------------------------------------------------------------------------
int main()
{
    srand(time(0));

    std::vector<ARG_TYPE> testVec;
    int iterations = 0;
    size_t dataLen = 0;

    std::cout << "enter a number of test cases to run: ";
    std::cin >> iterations;
    std::cout << "enter test data length per test case: ";
    std::cin >> dataLen;
    
    testVec.resize(iterations);

    std::cout << "making test data... " << std::endl;
    for(size_t k = 0; k < testVec.size(); ++k) {
        //testVec[k] = Benchmarking::makeRandomString(dataLen, "((((((()))))))");

        testVec[k] = generateRandomValue<ARG_TYPE>(dataLen);
    }
    
    for (size_t idx = 0; idx < sizeof(funcTable)/sizeof(funcTable[0]); ++idx)
    {
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "running benchmark for " << funcTable[idx].name << std::endl;

        const int warmUpIterations = 18;
        std::cout << "warming up for "<< warmUpIterations << " iterations ..." << std::endl;

        // Warm-up phase
        for (int i = 0; i < warmUpIterations && i < testVec.size(); ++i) {
            volatile auto result = funcTable[idx].func(testVec[i]);
            (void)result; // Prevents the compiler from optimizing away the call
        }

        std::cout << "testing for " << testVec.size() << " test cases ..." << std::endl;
        std::vector<RET_TYPE> resultVec;
        resultVec.resize(testVec.size());
        auto t1 = std::chrono::high_resolution_clock::now();
        for (size_t k = 0 ; k < testVec.size(); ++k)
        {
            //std::cout << "testing case " << k+1 << std::endl;
            // for (auto elem : testVec) {
            //     std::cout << elem << ", ";
            // }
            // std::cout << std::endl;

            resultVec[k] = funcTable[idx].func(testVec[k]);
            //std::cout << "resultVec[" << k << "] = " << resultVec[k] << std::endl;
        } 

        auto t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

        std::cout << "handling " << resultVec.size() << " test results" << std::endl;

        int result = handleResult(resultVec);

        std::cout << "result : " << result << std::endl;
        std::cout << "time: " <<  duration/1000.0 << "ms " << std::endl;
        std::cout << "iterations: " << iterations << ", at " << (1000 * duration) / iterations 
            << "ns per iteration" << std::endl;
    }
    return 0;
}
