#pragma once
#include <cmath>
#include <utility>

namespace MEN
{
	constexpr float pi = 3.14159265359f;
	constexpr float twoPi = 6.28318530718f; // pi * 2
	constexpr float halfPi = 1.57079632679f; // pi / 2

	constexpr float RadiansToDegrees(float radians) { return radians * (180.0f / pi); }
	constexpr float DegreesToRadians(float degrees) { return degrees * (pi / 180.0f); }

	//constexpr int Wrap(int value, int maxValue)
	//{
	//	return value % maxValue + ((value < 0) ? maxValue : 0);
	//}

	inline float Wrap(float value, float max)
	{
		return std::fmod(value, max) + ((value < 0) ? max : 0);
	}

	template <typename T> // allows one function to use different data types (Template)
	inline T Max(T a, T b)
	{
		return (a > b) ? a : b;
	}

	template <typename T>
	inline T Min(T a, T b)
	{
		return (a < b) ? a : b;
	}

	template <typename T>
	inline T Clamp(T value, T min, T max) //  4 - 10 -> 3
	{
		if (min > max) std::swap(min, max);

		return (value < min) ? min : (value > max) ? max : value; // if (value < min) return min : if (value > max) return max : else return value
	}

	template<typename T>
	constexpr T Lerp(const T& a, const T& b, float t) // T = 0 to 1
	{
		return (a * (1.0f - t)) + (b * t);
	}

}