#include "Enemy.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Framework/Emitter.h"
#include "Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Resource/ResourceManager.h"
#include "Player.h"

#include "Framework/Framework.h"

namespace MEN
{
	CLASS_DEFINITION(Enemy)

		bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<MEN::PhysicsComponent>();

		return true;
	}

	void Enemy::Update(float deltaTime)
	{
		Actor::Update(deltaTime);

		bool onGround = (groundCount < 0);
		vec2 velocity = m_physicsComponent->m_velocity;

		MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			MEN::Vector2 direction = player->transform.position - transform.position;
			velocity.x += speed * ((onGround) ? 1 : 0.5f) * deltaTime;
			velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
			m_physicsComponent->SetVelocity(velocity);
		}


		//transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{

		if (other->tag == "Player")
		{
			this->m_destroyed = true;
			other->m_destroyed = true;
			MEN::EventManager::Instance().DispatchEvent("OnAddPoints", 100);
			MEN::EventManager::Instance().DispatchEvent("OnEnemyDead", 0);
		}

		if (other->tag == "Ground") groundCount++;

	}

	void Enemy::OnCollisionExit(Actor* other)
	{

		if (other->tag == "Ground") groundCount--;

	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}
}