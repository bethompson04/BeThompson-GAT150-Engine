#include "Enemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "PewPew.h"
#include "PewGame.h"
#include "Framework/Emitter.h"

void Enemy::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(m_Transform.rotation);
	Player* player = m_scene->GetActor<Player>();
	if (player)
	{
		MEN::Vector2 direction = player->m_Transform.position - m_Transform.position;

		float turnAngle = MEN::vec2::SignedAngle(forward, direction.Normalized());

		m_Transform.rotation += turnAngle * 2 * deltaTime;

		if (std::fabs(turnAngle) < MEN::DegreesToRadians(30.0f))
		{
			// I see you
		}
	}


	m_Transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	m_Transform.position.x = MEN::Wrap(m_Transform.position.x, (float)MEN::g_renderer.GetWidth());
	m_Transform.position.y = MEN::Wrap(m_Transform.position.y, (float)MEN::g_renderer.GetHeight());

	// Decrement Timer
	m_fireTimer -= deltaTime;
	if (m_fireTimer <= 0)
	{
		MEN::Transform transform{m_Transform.position, m_Transform.rotation, 1};
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, transform, m_model);
		pewPew->m_tag = "Enemy_Bullet";
		m_scene->Add(std::move(pewPew));
		//Reset Timer
		m_fireTimer = m_fireRate;
	}
}

void Enemy::OnCollision(Actor* other)
{

	if (other->m_tag == "Rock")
	{
		this->m_destroyed = true;
	}
	// Player* p = dynamic_cast<Player*>(other)
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

		data.color = MEN::Color{ 1, 1, 0.5f, 1 };

		MEN::Transform transformP{ { m_Transform.position }, 0, 1 };
		std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
		emitter->m_lifespan = 0.2f;
		m_scene->Add(std::move(emitter));

	}

}
