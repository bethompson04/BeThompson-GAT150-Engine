#pragma once
#include "Component.h"
#include "Core/Vector2.h"

namespace MEN
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const vec2& force) = 0;
	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0 ;
		float m_damping = 0;
	};
}