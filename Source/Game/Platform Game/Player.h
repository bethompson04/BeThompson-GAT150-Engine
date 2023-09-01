#pragma once
#include "Framework/Actor.h"
#include "Framework/Components/PhysicsComponent.h"


namespace MEN
{
	class Player : public MEN::Actor
	{
	public:
		enum class playerState
		{
			REST,
			JUMP,
			ATTACK,
			ROLL,
			DEAD
		};
	public:
		CLASS_DECLARATION(Player)

			Player() = default;
		Player(float speed, float turnRate, const MEN::Transform& transform) :
			Actor(transform), speed{ speed }
		{}


		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

		playerState pState = playerState::REST;

	private:
		int attackType = 1;
		float attackTimer = 0;
		float speed = 0;
		float direction = 0;
		float tempDir = 0;
		float maxSpeed = 0;
		float jump = 0;
		int groundCount = 0;


		class PhysicsComponent* m_physicsComponent = nullptr;
		class SpriteAnimComponent* m_spriteAnimComponent = nullptr;
	};
}