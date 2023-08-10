#pragma once
#include <cmath>
#include <ostream>
#include <string>
#include <iostream>
namespace MEN
{
	class Vector3
	{
	public:
		float x, y, z;

	public:
		Vector3() : x{ 0 }, y{ 0 }, z{ 0 } {} //Initializes x and y to 0
		Vector3(float value) : x{ value }, y{ value }, z{ value } {}
		Vector3(float valueX, float valueY) : x{ valueX }, y{ valueY }, z{ 0 } {}
		Vector3(float valueX, float valueY, float valueZ) : x{ valueX }, y{ valueY }, z{ valueZ } {}
		Vector3(int valueX, int valueY) : x{ (float)valueX }, y{ (float)valueY }, z{ 0 } {}
		Vector3(int valueX, int valueY, int valueZ) : x{ (float)valueX }, y{ (float)valueY }, z{ (float)valueZ} {}

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		Vector3 operator - () const { return Vector3(-x, -y, -z); }
		//Vector3 Negate() const { return Vector3(-x, -y, -z); }

		//Vector3 Add(const Vector3& vector) const { return Vector3(x + vector.x, y + vector.y); }
		Vector3 operator + (const Vector3& vector) const { return Vector3(x + vector.x, y + vector.y, z + vector.z); }
		Vector3 operator - (const Vector3& vector) const { return Vector3(x - vector.x, y - vector.y, z - vector.z); }
		Vector3 operator / (const Vector3& vector) const { return Vector3(x / vector.x, y / vector.y, z / vector.z); }
		Vector3 operator * (const Vector3& vector) const { return Vector3(x * vector.x, y * vector.y, z * vector.z); }

		Vector3 operator + (float s) const { return Vector3(x + s, y + s, z + s); }
		Vector3 operator - (float s) const { return Vector3(x - s, y - s, z - s); }
		Vector3 operator / (float s) const { return Vector3(x / s, y / s, z / s); }
		Vector3 operator * (float s) const { return Vector3(x * s, y * s, z * s); }

		Vector3& operator += (const Vector3& vector) { x += vector.x; y += vector.y; z += vector.z; return *this; }
		Vector3& operator -= (const Vector3& vector) { x -= vector.x; y -= vector.y; z -= vector.z; return *this; }
		Vector3& operator /= (const Vector3& vector) { x /= vector.x; y /= vector.y; z /= vector.z; return *this; }
		Vector3& operator *= (const Vector3& vector) { x *= vector.x; y *= vector.y; z *= vector.z; return *this; }

		float LengthSqr() const { return (x * x) + (y * y); }
		float Length() const { return sqrt(LengthSqr()); }

		inline float DistanceSqr(const Vector3& vector) const { return (vector - *this).LengthSqr(); }
		inline float Distance(const Vector3& vector) const { return (vector - *this).Length(); }

		Vector3 Normalized() const { return *this / Length(); }
		void Normalize() { *this /= Length(); }

		static float Dot(const Vector3& v1, const Vector3& v2);
	private:

	};

	// get the dot product beteen v1 and v2 https://www.falstad.com/dotproduct/
	inline float Vector3::Dot(const Vector3& v1, const Vector3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	using vec3 = Vector3;
}
