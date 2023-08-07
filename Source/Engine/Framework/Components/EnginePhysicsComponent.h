#pragma once
#include "PhysicsComponent.h"

namespace MEN
{
	class EnginePhysicsComponent : public PhysicsComponent
	{

	public:

		virtual void Update(float deltaTime) override;
		virtual void ApplyForce(const vec2& force) override;
	};
}