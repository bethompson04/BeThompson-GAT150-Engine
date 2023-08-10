#pragma once
#include "Vector2.h"
#include "Matrix3x3.h"

namespace MEN
{
	class Transform
	{
	public:
		// Data
		vec2 position;
		float rotation = 0;
		float scale = 1;
	public:
		// Constructors and Functions
		Transform() = default;
		Transform(const vec2& position, float rotation, float scale = 1) :
			position{ position },
			rotation{ rotation },
			scale{ scale }
		{}

		mat3 GetMatrix() const
		{
			mat3 ms = mat3::CreateScale(scale);
			mat3 mr = mat3::CreateRotation(rotation);
			mat3 mt = mat3::CreateTranslation(position);

			return mt * ms * mr;
		}


	};
}