#include "Boss.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Weapon.h"
#include "PewGame.h"
#include "Framework/Emitter.h"
#include "Renderer/ModelManager.h"
#include "PewGame.h"
#include "Framework/Framework.h"

void Boss::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(transform.rotation);
	Player* player = m_scene->GetActor<Player>();

	// Decrement Timer
	m_fireTimer -= deltaTime;
	if (player)
	{
		MEN::Vector2 direction = player->transform.position - transform.position;

		float turnAngle = MEN::vec2::SignedAngle(forward, direction.Normalized());

		transform.rotation += turnAngle * 2 * deltaTime;

		if (std::fabs(turnAngle) < MEN::DegreesToRadians(30.0f))
		{
			if (m_fireTimer <= 0)
			{
				auto weapon = INSTANTIATE(Weapon, "Rocket_Enemy");
				weapon->transform = { transform.position, transform.rotation + MEN::DegreesToRadians(20), 1 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));

				weapon = INSTANTIATE(Weapon, "Rocket_Enemy");
				weapon->transform = { transform.position, transform.rotation - MEN::DegreesToRadians(20), 1 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));

				weapon = INSTANTIATE(Weapon, "Rocket_Enemy");
				weapon->transform = { transform.position, transform.rotation, 1 };
				weapon->Initialize();
				m_scene->Add(std::move(weapon));

				//Reset Timer
				m_fireTimer = m_fireRate;
			}
		}
	}

	transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
	transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());
}

void Boss::OnCollision(Actor* other)
{
	other->m_destroyed = true;
	if (other->tag == "Player" || other->tag == "Player_Bullet")
	{
		hits += 1;
		std::cout << "boss hit " << hits << std::endl;

	}

	if (hits >= hitsToDie)
	{
		if (other->tag == "Player" || other->tag == "Player_Bullet")
		{
			m_game->AddPoints(100);
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

			data.color = MEN::Color{ 1, 0.5466403f, 0 , 1};

			MEN::Transform transformP{ { transform.position }, 0, 1 };
			std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
			emitter->lifespan = 0.2f;
			m_scene->Add(std::move(emitter));

		}

		dynamic_cast<PewGame*>(m_game)->SetState(PewGame::eState::GameBossEnd);
	}
}