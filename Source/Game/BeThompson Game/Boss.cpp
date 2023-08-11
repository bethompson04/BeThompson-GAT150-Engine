#include "Boss.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "PewPew.h"
#include "PewGame.h"
#include "Framework/Emitter.h"
#include "Renderer/ModelManager.h"
#include "PewGame.h"
#include "Framework/Framework.h"

void Boss::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(m_Transform.rotation);
	Player* player = m_scene->GetActor<Player>();

	// Decrement Timer
	m_fireTimer -= deltaTime;
	if (player)
	{
		MEN::Vector2 direction = player->m_Transform.position - m_Transform.position;

		float turnAngle = MEN::vec2::SignedAngle(forward, direction.Normalized());

		m_Transform.rotation += turnAngle * 2 * deltaTime;

		if (std::fabs(turnAngle) < MEN::DegreesToRadians(30.0f))
		{
			if (m_fireTimer <= 0)
			{
				MEN::Transform transform{m_Transform.position, m_Transform.rotation, 1};
				std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, transform);
				pewPew->m_tag = "Enemy_Bullet";

				std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
				component->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);

				pewPew->AddComponent(std::move(component));

				auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				pewPew->AddComponent(std::move(collisionComponent));

				m_scene->Add(std::move(pewPew));

				MEN::Transform transform2 {m_Transform.position, m_Transform.rotation + MEN::DegreesToRadians(20.0f), 1};
				std::unique_ptr<PewPew> pewPew2 = std::make_unique<PewPew>("pew", 400.0f, transform2);
				pewPew2->m_tag = "Enemy_Bullet";

				std::unique_ptr<MEN::SpriteComponent> component2 = std::make_unique<MEN::SpriteComponent>();
				component2->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);

				pewPew2->AddComponent(std::move(component2));

				auto collisionComponent2 = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent2->m_radius = 30.0f;
				pewPew2->AddComponent(std::move(collisionComponent2));

				m_scene->Add(std::move(pewPew2));

				MEN::Transform transform3 {m_Transform.position, m_Transform.rotation - MEN::DegreesToRadians(20.0f), 1};
				std::unique_ptr<PewPew> pewPew3 = std::make_unique<PewPew>("pew", 400.0f, transform3);
				pewPew3->m_tag = "Enemy_Bullet";

				std::unique_ptr<MEN::SpriteComponent> component3 = std::make_unique<MEN::SpriteComponent>();
				component3->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);

				pewPew3->AddComponent(std::move(component3));

				auto collisionComponent3 = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent3->m_radius = 30.0f;
				pewPew3->AddComponent(std::move(collisionComponent3));

				m_scene->Add(std::move(pewPew3));

				//Reset Timer
				m_fireTimer = m_fireRate;
			}
		}
	}

	m_Transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	m_Transform.position.x = MEN::Wrap(m_Transform.position.x, (float)MEN::g_renderer.GetWidth());
	m_Transform.position.y = MEN::Wrap(m_Transform.position.y, (float)MEN::g_renderer.GetHeight());
}

void Boss::OnCollision(Actor* other)
{
	other->m_destroyed = true;
	if (other->m_tag == "Player" || other->m_tag == "Player_Bullet")
	{
		hits += 1;
		std::cout << "boss hit " << hits << std::endl;

	}

	if (hits >= hitsToDie)
	{
		if (other->m_tag == "Player" || other->m_tag == "Player_Bullet")
		{
			m_game->AddPoints(100);
			this->m_destroyed = true;

			MEN::EmitterData data;

			data.burst = false;
			data.burstCount = 0;
			data.spawnRate = 100;
			data.angle = m_Transform.rotation;
			data.angleRange = MEN::pi;
			data.lifeTimeMin = 0.6f;
			data.lifeTimeMax = 1.5f;
			data.speedMin = 100;
			data.speedMax = 250;
			data.damping = 0.9f;

			data.color = MEN::Color{ 1, 0.5466403f, 0 , 1};

			MEN::Transform transformP{ { m_Transform.position }, 0, 1 };
			std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
			emitter->m_lifespan = 0.2f;
			m_scene->Add(std::move(emitter));

		}

		dynamic_cast<PewGame*>(m_game)->SetState(PewGame::eState::GameBossEnd);
	}
}