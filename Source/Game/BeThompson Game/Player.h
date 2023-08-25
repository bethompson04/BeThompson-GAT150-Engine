#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"

namespace MEN
{
	class Player : public MEN::Actor
	{
	public:
		CLASS_DECLARATION(Player)

		Player() = default;
		Player(float speed, float turnRate, const MEN::Transform& transform) :
			Actor(transform), m_speed{ speed }, m_turnRate{ turnRate }
		{}


		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollisionEnter(Actor* other) override;

	private:
		float m_speed = 0;
		float m_turnRate = 0;

		bool multiShotx2 = false;
		bool multiShotx3 = false;

		void Shoot(vec2 forward);

		PhysicsComponent* m_physicsComponent = nullptr;
	};
}