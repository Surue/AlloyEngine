#pragma once

#include <cmath>
#include <cstdint>

namespace alloy{
template<typename T>
struct Vector2 {
    union
    {
        struct
        {
            T x;
            T y;

        };
        T coord[2];
    };

    const static Vector2 zero;
    const static Vector2 one;
    const static Vector2 up;
    const static Vector2 down;
    const static Vector2 left;
    const static Vector2 right;

    Vector2() : x(0), y(0){}

    Vector2(T x, T y) : x(x), y(y){}

    float Magnitude(){
        return std::sqrt(x * x + y * y);
    }
};

using fvec2 = Vector2<float>;
using ivec2 = Vector2<int>;
using i8vec2 = Vector2<int8_t>;
using i16vec2 = Vector2<int16_t>;
using i32vec2 = Vector2<int32_t>;
using i64vec2 = Vector2<int64_t>;

template<typename T>
inline Vector2<T> const Vector2<T>::zero = Vector2<T>(0, 0);
template<typename T>
inline Vector2<T> const Vector2<T>::one = Vector2<T>(1, 1);
template<typename T>
inline Vector2<T> const Vector2<T>::up = Vector2<T>(0, 1);
template<typename T>
inline Vector2<T> const Vector2<T>::down = Vector2<T>(0, -1);
template<typename T>
inline Vector2<T> const Vector2<T>::left = Vector2<T>(-1, 0);
template<typename T>
inline Vector2<T> const Vector2<T>::right = Vector2<T>(1, 0);
} //namespace alloy
