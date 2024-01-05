#ifndef BENCHMARKING_HPP
#define BENCHMARKING_HPP

#include <string>
#include <random>
#include <ctime>

#define INPUT_MAX 128

namespace Benchmarking
{
// -------------------------------------------------------------------------------------------------
template<typename ReturnType, typename... Args>
struct FuncEntry {
    typedef ReturnType (*funcptr)(Args...);  // Function pointer type
    funcptr func;
    const char* name;

    FuncEntry(funcptr f, const char* n) : func(f), name(n) {}  // Constructor
};

// -------------------------------------------------------------------------------------------------
template <typename T>
void makeRandomArray(std::vector<T> &arr)
{
    for (int k = 0; k < arr.size(); ++k)
    {
        arr[k] = T( (rand()) % INPUT_MAX + 1);
    }
    
    std::cout << "made random array: arr[0]: " << arr[0] << std::endl;
} 

// -------------------------------------------------------------------------------------------------
std::string makeRandomString(size_t length)
{
    const std::string characters = "abcdefghijklmnopqrstuvwxyz";
    std::default_random_engine randomEngine(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<size_t> distribution(0, characters.size() - 1);
    std::string randomString;
    for (size_t i = 0; i < length; ++i) {
        randomString += characters[distribution(randomEngine)];
    }

    return randomString;
} 


}

#endif