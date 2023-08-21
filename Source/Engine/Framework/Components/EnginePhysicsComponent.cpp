#include "EnginePhysicsComponent.h"
#include "Framework/Actor.h"

namespace MEN
{
	CLASS_DEFINITION(EnginePhysicsComponent)

	void EnginePhysicsComponent::Update(float deltaTime)
	{
		m_owner->transform.position += m_velocity * deltaTime;
		m_velocity *= std::pow(1 - m_damping, deltaTime);
	}

	void EnginePhysicsComponent::ApplyForce(const vec2& force)
	{
		m_velocity += force;
	}

	void MEN::EnginePhysicsComponent::Read(const json_t& value)
	{

	}
}
