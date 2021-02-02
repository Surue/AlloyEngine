#pragma once

#include <cmath>
#include <cstdint>

namespace alloy::math {
template <typename T> struct Vector2 {
	union {
		struct {
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
	const static Vector2 downRight;
	const static Vector2 downLeft;
	const static Vector2 upRight;
	const static Vector2 upLeft;

	Vector2() : x(0), y(0) {}

	Vector2(T x, T y) : x(x), y(y) {}

	Vector2 operator + (const Vector2 rhs) const {
		return { x + rhs.x, y + rhs.y };
	}
	
	Vector2 operator / (const Vector2 rhs) const {
		return { x / rhs.x, y / rhs.y };
	}

	float Magnitude() {
		return std::sqrt(x * x + y * y);
	}
};

using fvec2 = Vector2<float>;
using ivec2 = Vector2<int>;
using i8vec2 = Vector2<int8_t>;
using i16vec2 = Vector2<int16_t>;
using i32vec2 = Vector2<int32_t>;
using i64vec2 = Vector2<int64_t>;
using uivec2 = Vector2<unsigned int>;

template <typename T> inline Vector2<T> const Vector2<T>::zero = Vector2<T>(0, 0);
template <typename T> inline Vector2<T> const Vector2<T>::one = Vector2<T>(1, 1);
template <typename T> inline Vector2<T> const Vector2<T>::up = Vector2<T>(0, -1);
template <typename T> inline Vector2<T> const Vector2<T>::down = Vector2<T>(0, 1);
template <typename T> inline Vector2<T> const Vector2<T>::left = Vector2<T>(-1, 0);
template <typename T> inline Vector2<T> const Vector2<T>::right = Vector2<T>(1, 0);
template <typename T> inline Vector2<T> const Vector2<T>::downRight = down + right;
template <typename T> inline Vector2<T> const Vector2<T>::downLeft = down + left;
template <typename T> inline Vector2<T> const Vector2<T>::upRight = up + right;
template <typename T> inline Vector2<T> const Vector2<T>::upLeft = up + left;

template <typename T> struct Vector3 {
	union {
		struct {
			T x;
			T y;
			T z;

		};

		T coord[2];
	};

	const static Vector3 zero;
	const static Vector3 one;

	Vector3() : x(0), y(0), z(0) {}

	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

	Vector3 operator + (const Vector3 rhs) const {
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vector3 operator / (const Vector3 rhs) const {
		return { x / rhs.x, y / rhs.y, z / rhs.z };
	}

	float Magnitude() {
		return std::sqrt(x * x + y * y + z * z);
	}
};

using fvec3 = Vector3<float>;
using ivec3 = Vector3<int>;
using i8vec3 = Vector3<int8_t>;
using i16vec3 = Vector3<int16_t>;
using i32vec3 = Vector3<int32_t>;
using i64vec3 = Vector3<int64_t>;
using uivec3 = Vector3<unsigned int>;

template <typename T> inline Vector3<T> const Vector3<T>::zero = Vector3<T>(0, 0, 0);
template <typename T> inline Vector3<T> const Vector3<T>::one = Vector3<T>(1, 1, 1);
}
