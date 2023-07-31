#pragma once
#include "Vector2.h"

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
		{

		}


	};
}