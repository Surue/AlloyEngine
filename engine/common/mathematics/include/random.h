#pragma once
#include <random>

//TODO refactor randoms 
namespace math {
template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type RandomRange(T start, T end)
{
    static std::random_device rd;  
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<T> dis(start, end);
    return dis(gen);
}

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type RandomRange(T start, T end)
{
    static std::random_device rd;  
    static std::mt19937 gen(rd()); 
    std::uniform_real_distribution<T> dis(start, end);
    return dis(gen);
}
} //namespace maths