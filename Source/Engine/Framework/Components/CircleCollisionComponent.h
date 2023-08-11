#pragma once
#include "CollisionComponent.h"

namespace MEN
{
	class CircleCollisionComponent : public CollisionComponent
	{
	public:

		virtual void Update(float deltaTime) override;
		virtual bool CheckCollision(CollisionComponent* collision) override;
	};
}