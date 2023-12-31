#pragma once
#include "Component.h"
#include "Core/Math/Vector2.h"

namespace MEN
{
	class PhysicsComponent : public Component
	{
	public:
		virtual void ApplyForce(const vec2& force) = 0;
		virtual void ApplyTorque(float torque) = 0;

		virtual void SetVelocity(const vec2& velocity) { this->m_velocity = velocity; }
		virtual void SetGravityScale(float scale) {}

	public:
		vec2 m_velocity;
		vec2 m_acceleration;
		float m_mass = 1.0 ;
		float m_damping = 0;
	};
}