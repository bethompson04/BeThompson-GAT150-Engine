#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Weapon.h"
#include "PewGame.h"
#include "Framework/Emitter.h"
#include "Framework/Framework.h"

namespace MEN
{
	CLASS_DEFINITION(Enemy)

	bool Enemy::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<MEN::PhysicsComponent>();
		auto collisionComponent = GetComponent<MEN::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = GetComponent<MEN::RenderComponent>();
			if (renderComponent)
			{
				float scale = transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;

			}
		}
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

			float turnAngle = MEN::vec2::SignedAngle(forward, direction.Normalized());

			//transform.rotation += turnAngle * 2 * deltaTime;

			m_physicsComponent->ApplyTorque(turnAngle);

			if (std::fabs(turnAngle) < MEN::DegreesToRadians(30.0f))
			{
				// I see you
				m_fireTimer -= deltaTime;
				if (m_fireTimer <= 0)
				{
					auto weapon = INSTANTIATE(Weapon, "Rocket_Enemy");
					weapon->transform = { transform.position, transform.rotation, 1 };
					weapon->Initialize();
					m_scene->Add(std::move(weapon));

					//Reset Timer
					m_fireTimer = m_fireRate;
				}
			}
		}

		m_physicsComponent->ApplyForce(forward * m_speed);

		//transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

		transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
		transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());

		// Decrement Timer
	}

	void Enemy::OnCollision(Actor* other)
	{

		if (other->tag == "Rock")
		{
			this->m_destroyed = true;
		}
		// Player* p = dynamic_cast<Player*>(other)
		if (other->tag == "Player" || other->tag == "Player_Bullet")
		{
			MEN::EventManager::Instance().DispatchEvent("OnAddPoints", 100);
			//m_game->AddPoints(100);
			this->m_destroyed = true;

			MEN::EmitterData data;

			data.burst = false;
			data.burstCount = 0;
			data.spawnRate = 100;
			data.angle = transform.rotation;
			data.angleRange = MEN::pi;
			data.lifeTimeMin = 0.6f;
			data.lifeTimeMax = 1.5f;
			data.speedMin = 100;
			data.speedMax = 250;
			data.damping = 0.9f;

			data.color = MEN::Color{ 1, 1, 0.5f, 1 };

			MEN::Transform transformP{ { this->transform.position }, 0, 1 };
			std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
			emitter->lifespan = 0.2f;
			m_scene->Add(std::move(emitter));

		}
	}

	void Enemy::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, m_speed);
		READ_DATA(value, m_turnRate);
		READ_DATA(value, m_fireRate);
	}
}
