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

		MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(transform.rotation);
		Player* player = m_scene->GetActor<Player>();
		if (player)
		{
			MEN::Vector2 direction = player->transform.position - transform.position;
			m_physicsComponent->ApplyForce(direction.Normalized() * speed);
		}


		//transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

		transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
		transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());

	}

	void Enemy::OnCollisionEnter(Actor* other)
	{

		if (other->tag == "Enemy")
		{
			this->m_destroyed = true;
			other->m_destroyed = true;
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