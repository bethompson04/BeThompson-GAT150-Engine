#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace MEN
{
	class Enemy : public MEN::Actor
	{
	public:
		CLASS_DECLARATION(Enemy)

			Enemy() = default;
		Enemy(float speed, float turnRate, const MEN::Transform& transform) :
			Actor(transform), speed{ speed }
		{}


		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

	private:
		float speed = 0;
		float jump = 0;
		int groundCount = 0;


		PhysicsComponent* m_physicsComponent = nullptr;
	};
}