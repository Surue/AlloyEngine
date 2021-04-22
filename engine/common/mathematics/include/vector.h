#pragma once

#include <cmath>
#include <cstdint>

namespace math {
template <typename T>
struct Vector2 {
	
	T x;
	T y;

	Vector2() : x(0), y(0) {}

	Vector2(T x, T y) : x(x), y(y) {}

	//TODO move all those method/operator in a .impl file
	Vector2 operator + (const Vector2 rhs) const {
		return { x + rhs.x, y + rhs.y };
	}

	Vector2& operator += (const Vector2 rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2 operator - (const Vector2 rhs) const {
		return { x - rhs.x, y - rhs.y };
	}

	Vector2& operator -= (const Vector2 rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector2 operator / (const float scalar) const {
		return { x / scalar, y / scalar };
	}

	Vector2& operator /= (const float scalar) {
		x /= scalar;
		y /= scalar;
		return *this;
	}
	
	Vector2 operator / (const Vector2 rhs) const {
		return { x / rhs.x, y / rhs.y };
	}

	Vector2 operator * (const float scalar) const {
		return { x * scalar, y * scalar };
	}

	Vector2& operator *= (const float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	float SqrMagnitude() const {
		return x * x + y * y;
	}

	float Magnitude() const {
		return std::sqrt(x * x + y * y);
	}

	float Dot(const Vector2 other) const {
		return x * other.x + y * other.y;
	}

	void Normalize() {
		*this /= Magnitude();
	}

	Vector2 Normalized() {
		return *this / Magnitude();
	}

	// Base vectors 2
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

template <typename T>
struct Vector3 {
	
	T x;
	T y;
	T z;

	Vector3() : x(0), y(0), z(0) {}

	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

	Vector3 operator + (const Vector3& rhs) const {
		return { x + rhs.x, y + rhs.y, z + rhs.z };
	}

	Vector3 operator / (const Vector3& rhs) const {
		return { x / rhs.x, y / rhs.y, z / rhs.z };
	}

	float Magnitude() {
		return std::sqrt(x * x + y * y + z * z);
	}

	float Dot(const Vector3& other) const {
		return x * other.x + y * other.y + z * other.z;
	}

	const static Vector3 zero;
	const static Vector3 one;
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
}  // namespace math
