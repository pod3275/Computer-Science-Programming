#pragma once

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
// C standard
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// STL
#include <algorithm>
#include <array>
#include <map>
#include <set>
#include <string>
#include <vector>
// C++11
#if (_MSC_VER>=1600/*VS2010*/) || (__cplusplus>199711L)
#include <functional>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#endif
// windows/GCC
#if !defined(__GNUC__)&&(defined(_WIN32)||defined(_WIN64))
#include <windows.h>
#include <wchar.h>
#elif defined(__GNUC__)&&!defined(__forceinline)
#define __forceinline inline __attribute__((__always_inline__))
#endif
// common macros
#ifndef PI
#define PI 3.141592653589793f
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef clamp
#define clamp(value,vmin,vmax) (max(vmin,min(vmax,value)))
#endif
#ifndef isnan
#define	isnan(x) (x!=x)
#endif

//*******************************************************************
// user types
typedef unsigned int	uint;
typedef unsigned short	ushort;
typedef unsigned char	uchar;

// template constants
template <class T> struct precision { static const T value() { return std::numeric_limits<T>::epsilon() * 10; } };	// need to be 10x for robust practical test

																													//*******************************************************************
template <class T> struct tvec2
{
	union { struct { T r, g; }; struct { T x, y; }; };

	// constructor/set
	tvec2() { x = y = 0; }
	tvec2(T a) { x = y = a; }						inline void set(T a) { x = y = a; }
	tvec2(T a, T b) { x = a; y = b; }				inline void set(T a, T b) { x = a; y = b; }
	tvec2(const tvec2& v) { x = v.x; y = v.y; }		inline void set(const tvec2& v) { x = v.x; y = v.y; }
	tvec2(const T* a) { x = a[0]; y = a[1]; }		inline void set(const T* a) { x = a[0]; y = a[1]; }

	// assignment / compound assignment operators
	inline tvec2& operator=(T a) { set(a); return *this; }
	inline tvec2& operator+=(const tvec2& v) { x += v.x; y += v.y; return *this; }
	inline tvec2& operator-=(const tvec2& v) { x -= v.x; y -= v.y; return *this; }
	inline tvec2& operator*=(const tvec2& v) { x *= v.x; y *= v.y; return *this; }
	inline tvec2& operator/=(const tvec2& v) { x /= v.x; y /= v.y; return *this; }
	inline tvec2& operator+=(T a) { x += a; y += a; return *this; }
	inline tvec2& operator-=(T a) { x -= a; y -= a; return *this; }
	inline tvec2& operator*=(T a) { x *= a; y *= a; return *this; }
	inline tvec2& operator/=(T a) { x /= a; y /= a; return *this; }

	// comparison operators
	inline bool operator==(const tvec2& v) const { return std::abs(x - v.x) <= precision<T>::value() && std::abs(y - v.y) <= precision<T>::value(); }
	inline bool operator!=(const tvec2& v) const { return !operator==(v); }

	// casting operators
	inline operator T*() { return &x; }
	inline operator const T*() const { return &x; }

	// array access operators
	inline T& operator[](int i) { return (i == 0 ? x : y); }
	inline const T& operator[](int i) const { return (i == 0 ? x : y); }
	inline T& at(int i) { if (i < 0 || i >= 2) throw std::out_of_range("error"); return operator[](i); }
	inline const T& at(int i) const { if (i < 0 || i >= 2) throw std::out_of_range("error"); return operator[](i); }

	// unary operators
	inline tvec2 operator+() const { return tvec2(x, y); }
	inline tvec2 operator-() const { return tvec2(-x, -y); }

	// binary operators
	inline tvec2 operator+(const tvec2& v) const { return tvec2(x + v.x, y + v.y); }
	inline tvec2 operator-(const tvec2& v) const { return tvec2(x - v.x, y - v.y); }
	inline tvec2 operator*(const tvec2& v) const { return tvec2(x * v.x, y * v.y); }
	inline tvec2 operator/(const tvec2& v) const { return tvec2(x / v.x, y / v.y); }
	inline tvec2 operator+(T a) const { return tvec2(x + a, y + a); }
	inline tvec2 operator-(T a) const { return tvec2(x - a, y - a); }
	inline tvec2 operator*(T a) const { return tvec2(x * a, y * a); }
	inline tvec2 operator/(T a) const { return tvec2(x / a, y / a); }

	// length, normalize, dot product
	inline T length() const { return T(sqrt(x*x + y*y)); }
	inline T dot(const tvec2& v) const { return T(x*v.x + y*v.y); }
	inline tvec2 normalize() const { return tvec2(x / length(), y / length()); }
};

//*******************************************************************
template <class T> struct tvec3
{
	union { struct { T r, g, b; }; struct { T x, y, z; }; };

	// constructor/set
	tvec3() { x = y = z = 0; }
	tvec3(T a) { x = y = z = a; }								inline void set(T a) { x = y = z = a; }
	tvec3(T a, T b, T c) { x = a; y = b; z = c; }					inline void set(T a, T b, T c) { x = a; y = b; z = c; }
	tvec3(const tvec3& v) { x = v.x; y = v.y; z = v.z; }			inline void set(const tvec3& v) { x = v.x; y = v.y; z = v.z; }
	tvec3(const T* a) { x = a[0]; y = a[1]; z = a[2]; }			inline void set(const T* a) { x = a[0]; y = a[1]; z = a[2]; }
	tvec3(const tvec2<T>& v, T c) { x = v.x; y = v.y; z = c; }		inline void set(const tvec2<T>& v, T c) { x = v.x; y = v.y; z = c; }
	tvec3(T a, const tvec2<T>& v) { x = a; y = v.x; z = v.y; }		inline void set(T a, const tvec2<T>& v) { x = a; y = v.x; z = v.y; }

	// assignment / compound assignment operators
	inline tvec3& operator=(T a) { set(a); return *this; }
	inline tvec3& operator=(const T* a) { set(a); return *this; }
	inline tvec3& operator+=(const tvec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
	inline tvec3& operator-=(const tvec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	inline tvec3& operator*=(const tvec3& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	inline tvec3& operator/=(const tvec3& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
	inline tvec3& operator+=(T a) { x += a; y += a; z += a; return *this; }
	inline tvec3& operator-=(T a) { x -= a; y -= a; z -= a; return *this; }
	inline tvec3& operator*=(T a) { x *= a; y *= a; z *= a; return *this; }
	inline tvec3& operator/=(T a) { x /= a; y /= a; z /= a; return *this; }

	// comparison operators
	inline bool operator==(const tvec3& v) const { return std::abs(x - v.x) <= precision<T>::value() && std::abs(y - v.y) <= precision<T>::value() && std::abs(z - v.z) <= precision<T>::value(); }
	inline bool operator!=(const tvec3& v) const { return !operator==(v); }

	// casting operators
	inline operator T*() { return &x; }
	inline operator const T*() { return &x; }

	// array access operators
	inline T& operator[](int i) { if (i == 0) return x; else if (i == 1) return y; else return z; }
	inline const T& operator[](int i) const { if (i == 0) return x; else if (i == 1) return y; else return z; }
	inline T& at(int i) { if (i < 0 || i >= 3) throw std::out_of_range("error"); return operator[](i); }
	inline const T& at(int i) const { if (i < 0 || i >= 3) throw std::out_of_range("error"); return operator[](i); }

	// unary operators
	inline tvec3 operator+() const { return tvec3(x, y, z); }
	inline tvec3 operator-() const { return tvec3(-x, -y, -z); }

	// binary operators
	inline tvec3 operator+(const tvec3& v) const { return tvec3(x + v.x, y + v.y, z + v.z); }
	inline tvec3 operator-(const tvec3& v) const { return tvec3(x - v.x, y - v.y, z - v.z); }
	inline tvec3 operator*(const tvec3& v) const { return tvec3(x * v.x, y * v.y, z * v.z); }
	inline tvec3 operator/(const tvec3& v) const { return tvec3(x / v.x, y / v.y, z / v.z); }
	inline tvec3 operator+(T a) const { return tvec3(x + a, y + a, z + a); }
	inline tvec3 operator-(T a) const { return tvec3(x - a, y - a, z - a); }
	inline tvec3 operator*(T a) const { return tvec3(x * a, y * a, z * a); }
	inline tvec3 operator/(T a) const { return tvec3(x / a, y / a, z / a); }

	// length, normalize, dot product
	inline T length() const { return T(sqrt(x*x + y*y + z*z)); }
	inline tvec3 normalize() const { return tvec3(x / length(), y / length(), z / length()); }
	inline T dot(const tvec3& v) const { return T(x*v.x + y*v.y + z*v.z); }

	// tvec3 only: cross product
	inline tvec3 operator^(const tvec3& v) const { return tvec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }
	inline tvec3 cross(const tvec3& v) const { return tvec3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x); }
};

//*******************************************************************
template <class T> struct tvec4
{
	union { struct { T r, g, b, a; }; struct { T x, y, z, w; }; };

	// constructor/set
	tvec4() { x = y = z = w = 0; }
	tvec4(T a) { x = y = z = w = a; }										inline void set(T a) { x = y = z = w = a; }
	tvec4(T a, T b, T c, T d) { x = a; y = b; z = c; w = d; }					inline void set(T a, T b, T c, T d) { x = a; y = b; z = c; w = d; }
	tvec4(const tvec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }				inline void set(const tvec4& v) { x = v.x; y = v.y; z = v.z; w = v.w; }
	tvec4(const T* a) { x = a[0]; y = a[1]; z = a[2]; w = a[3]; }				inline void set(const T* a) { x = a[0]; y = a[1]; z = a[2]; w = a[3]; }
	tvec4(const tvec2<T>& v, T c, T d) { x = v.x; y = v.y; z = c; w = d; }	inline void set(const tvec2<T>& v, T c, T d) { x = v.x; y = v.y; z = c; w = d; }
	tvec4(T a, T b, const tvec2<T>& v) { x = a; y = b; z = v.x; w = v.y; }	inline void set(T a, T b, const tvec2<T>& v) { x = a; y = b; z = v.x; w = v.y; }
	tvec4(const tvec3<T>& v, T d) { x = v.x; y = v.y; z = v.z; w = d; }		inline void set(const tvec3<T>& v, T d) { x = v.x; y = v.y; z = v.z; w = d; }
	tvec4(T a, const tvec3<T>& v) { x = a; y = v.x; z = v.y; w = v.z; }		inline void set(T a, const tvec3<T>& v) { x = a; y = v.x; z = v.y; w = v.z; }
	tvec4(const tvec2<T>& v1, const tvec2<T>& v2) { x = v1.x; y = v1.y; z = v2.x; w = v2.y; }
	inline void set(const tvec2<T>& v1, const tvec2<T>& v2) { x = v1.x; y = v1.y; z = v2.x; w = v2.y; }

	// assignment / compound assignment operators
	inline tvec4& operator=(T a) { set(a); return *this; }
	inline tvec4& operator=(const T* a) { set(a); return *this; }
	inline tvec4& operator+=(const tvec4& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	inline tvec4& operator-=(const tvec4& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	inline tvec4& operator*=(const tvec4& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	inline tvec4& operator/=(const tvec4& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	inline tvec4& operator+=(T a) { x += a; y += a; z += a; w += a; return *this; }
	inline tvec4& operator-=(T a) { x -= a; y -= a; z -= a; w -= a; return *this; }
	inline tvec4& operator*=(T a) { x *= a; y *= a; z *= a; w *= a; return *this; }
	inline tvec4& operator/=(T a) { x /= a; y /= a; z /= a; w /= a; return *this; }

	// comparison operators
	inline bool operator==(const tvec4& v) const { return std::abs(x - v.x) <= precision<T>::value() && std::abs(y - v.y) <= precision<T>::value() && std::abs(z - v.z) <= precision<T>::value() && std::abs(w - v.w) <= precision<T>::value(); }
	inline bool operator!=(const tvec4& v) const { return !operator==(v); }

	// casting operators
	inline operator T*() { return &x; }
	inline operator const T*() { return &x; }

	// array access operators
	inline T& operator[](int i) { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else return w; }
	inline const T& operator[](int i) const { if (i == 0) return x; else if (i == 1) return y; else if (i == 2) return z; else return w; }
	inline T& at(int i) { if (i < 0 || i >= 4) throw std::out_of_range("error"); return operator[](i); }
	inline const T& at(int i) const { if (i < 0 || i >= 4) throw std::out_of_range("error"); return operator[](i); }

	// unary operators
	inline tvec4 operator+() const { return tvec4(x, y, z, w); }
	inline tvec4 operator-() const { return tvec4(-x, -y, -z, -w); }

	// binary operators
	inline tvec4 operator+(const tvec4& v) const { return tvec4(x + v.x, y + v.y, z + v.z, w + v.w); }
	inline tvec4 operator-(const tvec4& v) const { return tvec4(x - v.x, y - v.y, z - v.z, w - v.w); }
	inline tvec4 operator*(const tvec4& v) const { return tvec4(x * v.x, y * v.y, z * v.z, w * v.w); }
	inline tvec4 operator/(const tvec4& v) const { return tvec4(x / v.x, y / v.y, z / v.z, w / v.w); }
	inline tvec4 operator+(T a) const { return tvec4(x + a, y + a, z + a, w + a); }
	inline tvec4 operator-(T a) const { return tvec4(x - a, y - a, z - a, w - a); }
	inline tvec4 operator*(T a) const { return tvec4(x * a, y * a, z * a, w * a); }
	inline tvec4 operator/(T a) const { return tvec4(x / a, y / a, z / a, w / a); }

	// length, normalize, dot product
	inline T length() const { return T(sqrt(x*x + y*y + z*z + w*w)); }
	inline tvec4 normalize() const { return tvec4(x / length(), y / length(), z / length(), w / length()); }
	inline T dot(const tvec4& v) const { return T(x*v.x + y*v.y + z*v.z + w*v.w); }
};

//*******************************************************************
// type definitions
using vec2 = tvec2<float>;		using vec3 = tvec3<float>;		using vec4 = tvec4<float>;
using ivec2 = tvec2<int>;		using ivec3 = tvec3<int>;		using ivec4 = tvec4<int>;
using uvec2 = tvec2<uint>;		using uvec3 = tvec3<uint>;		using uvec4 = tvec4<uint>;
using dvec2 = tvec2<double>;	using dvec3 = tvec3<double>;	using dvec4 = tvec4<double>;

//*******************************************************************
// matrix 4x4: uses a standard row-major notation
struct mat4
{
	union { float a[16]; struct { float _11, _12, _13, _14, _21, _22, _23, _24, _31, _32, _33, _34, _41, _42, _43, _44; }; };

	mat4() { _12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f; _11 = _22 = _33 = _44 = 1.0f; }
	mat4(float* f) { memcpy(a, f, sizeof(float) * 16); }
	mat4(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34, float f41, float f42, float f43, float f44) { _11 = f11; _12 = f12; _13 = f13; _14 = f14; _21 = f21; _22 = f22; _23 = f23; _24 = f24; _31 = f31; _32 = f32; _33 = f33; _34 = f34; _41 = f41; _42 = f42; _43 = f43; _44 = f44; }

	// comparison operators
	inline bool operator==(const mat4& m) const { for (int k = 0; k<std::extent<decltype(a)>::value; k++) if (std::abs(a[k] - m[k])>precision<float>::value()) return false; return true; }
	inline bool operator!=(const mat4& m) const { return !operator==(m); }

	// casting
	inline operator float*() { return a; }
	inline operator const float*() const { return a; }

	// array access operator
	inline float& operator[](unsigned i) { if(i >= 16) throw std::out_of_range("error"); return a[i]; }
	inline float& operator[](int i) { if (i < 0 || i >= 16) throw std::out_of_range("error"); return a[i]; }
	inline const float& operator[](unsigned i) const { if (i >= 16) throw std::out_of_range("error"); return a[i]; }
	inline const float& operator[](int i) const { if (i < 0 || i >= 16) throw std::out_of_range("error"); return a[i]; }

	// identity and transpose
	static mat4 identity() { return mat4(); }
	inline void setIdentity() { _12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0.0f; _11 = _22 = _33 = _44 = 1.0f; }
	inline mat4 transpose() const { return mat4(_11, _21, _31, _41, _12, _22, _32, _42, _13, _23, _33, _43, _14, _24, _34, _44); }

	// binary operators
	inline vec4 operator*(const vec4& v) const { return vec4(_11*v.x + _12*v.y + _13*v.z + _14*v.w, _21*v.x + _22*v.y + _23*v.z + _24*v.w, _31*v.x + _32*v.y + _33*v.z + _34*v.w, _41*v.x + _42*v.y + _43*v.z + _44*v.w); }
	inline mat4 operator*(mat4& m) const {
		mat4 trans = m.transpose();
		float k[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		int count = 0;
		for (int i = 0; i < 16; i+=4) {
			for (int j = 0; j < 16; j+=4) {
				for (int l = 0; l < 4; l++) {
					k[count] += a[i + l] * trans[j + l];
				}
				count++;
			}
		}

		return mat4(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);
	}

	// determinant and inverse: see below for implemenations
	inline float determinant() const;
	inline mat4 inverse() const;
};

inline float mat4::determinant() const
{
	return _11*(_22*(_33*_44 - _34*_43) - _23*(_32*_44 - _34*_42) + _24*(_32*_43 - _33*_42))
		- _12*(_21*(_33*_44 - _34*_43) - _23*(_31*_44 - _34*_41) + _24*(_31*_43 - _33*_41))
		+ _13*(_21*(_32*_44 - _34*_42) - _22*(_31*_44 - _34*_41) + _24*(_31*_42 - _32*_41))
		- _14*(_21*(_32*_43 - _33*_42) - _22*(_31*_43 - _33*_41) + _23*(_31*_42 - _32*_41));

}

inline mat4 mat4::inverse() const
{
	float det = determinant(), k[16];
	if (det == 0) printf("mat4::inverse() might be singular.\n");
	k[0] = (_22*_33*_44 + _23*_34*_42 + _24*_32*_43 - _22*_34*_43 - _23*_32*_44 - _24*_33*_42) / determinant();
	k[1] = (_12*_34*_43 + _13*_32*_44 + _14*_33*_42 - _12*_33*_44 - _13*_34*_42 - _14*_32*_43) / determinant();
	k[2] = (_12*_23*_44 + _13*_24*_42 + _14*_22*_43 - _12*_24*_43 - _13*_22*_44 - _14*_23*_42) / determinant();
	k[3] = (_12*_24*_33 + _13*_22*_34 + _14*_23*_32 - _12*_23*_34 - _13*_24*_32 - _14*_22*_33) / determinant();
	k[4] = (_21*_34*_43 + _23*_31*_44 + _24*_33*_41 - _21*_33*_44 - _23*_34*_41 - _24*_31*_43) / determinant();
	k[5] = (_11*_33*_44 + _13*_34*_41 + _14*_31*_43 - _11*_34*_43 - _13*_31*_44 - _14*_33*_41) / determinant();
	k[6] = (_11*_24*_43 + _13*_21*_44 + _14*_23*_41 - _11*_23*_44 - _13*_24*_41 - _14*_21*_43) / determinant();
	k[7] = (_11*_23*_34 + _13*_24*_31 + _14*_21*_33 - _11*_24*_33 - _13*_21*_34 - _14*_23*_31) / determinant();
	k[8] = (_21*_32*_44 + _22*_34*_41 + _24*_31*_42 - _21*_34*_42 - _22*_31*_44 - _24*_32*_41) / determinant();
	k[9] = (_11*_34*_42 + _12*_31*_44 + _14*_32*_41 - _11*_32*_44 - _12*_34*_41 - _14*_31*_42) / determinant();
	k[10] = (_11*_22*_44 + _12*_24*_41 + _14*_21*_42 - _11*_24*_42 - _12*_21*_44 - _14*_22*_41) / determinant();
	k[11] = (_11*_24*_32 + _12*_21*_34 + _14*_22*_31 - _11*_22*_34 - _12*_24*_31 - _14*_21*_32) / determinant();
	k[12] = (_21*_33*_42 + _22*_31*_43 + _23*_32*_41 - _21*_32*_43 - _22*_33*_41 - _23*_31*_42) / determinant();
	k[13] = (_11*_32*_43 + _12*_33*_41 + _13*_31*_42 - _11*_33*_42 - _12*_31*_43 - _13*_32*_41) / determinant();
	k[14] = (_11*_23*_42 + _12*_21*_43 + _13*_22*_41 - _11*_22*_43 - _12*_23*_41 - _13*_21*_42) / determinant();
	k[15] = (_11*_22*_33 + _12*_23*_31 + _13*_21*_32 - _11*_23*_32 - _12*_21*_33 - _13*_22*_31) / determinant();
	return mat4(k[0], k[1], k[2], k[3], k[4], k[5], k[6], k[7], k[8], k[9], k[10], k[11], k[12], k[13], k[14], k[15]);
}