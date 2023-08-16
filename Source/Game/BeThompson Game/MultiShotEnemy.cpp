#include "MultiShotEnemy.h"
#include "Renderer/Renderer.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "PewComponent.h"
#include "PewGame.h"
#include "Framework/Emitter.h"
#include "Framework/Framework.h"


void MultiShotEnemy::Update(float deltaTime)
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
				MEN::Transform m_transform{transform.position, transform.rotation, 1};
				std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, m_transform);
				pewPew->tag = "Enemy_Bullet";

				std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
				component->m_texture = GET_RESOURCE(MEN::Texture, "rocket.png", MEN::g_renderer);

				pewPew->AddComponent(std::move(component));

				auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent->m_radius = 30.0f;
				pewPew->AddComponent(std::move(collisionComponent));

				m_scene->Add(std::move(pewPew));

				MEN::Transform m_transform2 {transform.position, transform.rotation + MEN::DegreesToRadians(20.0f), 1};
				std::unique_ptr<PewPew> pewPew2 = std::make_unique<PewPew>("pew", 400.0f, m_transform2);
				pewPew2->tag = "Enemy_Bullet";

				std::unique_ptr<MEN::SpriteComponent> component2 = std::make_unique<MEN::SpriteComponent>();
				component2->m_texture = GET_RESOURCE(MEN::Texture, "rocket.png", MEN::g_renderer);

				pewPew2->AddComponent(std::move(component2));

				auto collisionComponent2 = std::make_unique<MEN::CircleCollisionComponent>();
				collisionComponent2->m_radius = 30.0f;
				pewPew2->AddComponent(std::move(collisionComponent2));

				m_scene->Add(std::move(pewPew2));

				MEN::Transform m_transform3 {transform.position, transform.rotation - MEN::DegreesToRadians(20.0f), 1};
				std::unique_ptr<PewPew> pewPew3 = std::make_unique<PewPew>("pew", 400.0f, m_transform3);
				pewPew3->tag = "Enemy_Bullet";

				std::unique_ptr<MEN::SpriteComponent> component3 = std::make_unique<MEN::SpriteComponent>();
				component3->m_texture = GET_RESOURCE(MEN::Texture, "rocket.png", MEN::g_renderer);

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

	transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
	transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());
}

void MultiShotEnemy::OnCollision(Actor* other)
{
	if (other->tag == "Rock")
	{
		this->m_destroyed = true;
	}


	if (other->tag == "Player" || other->tag == "Player_Bullet")
	{
		m_game->AddPoints(250);
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

		data.color = MEN::Color{0.4948461f, 0.4560005f, 1};

		MEN::Transform transformP{ { transform.position }, 0, 1 };
		std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
		emitter->lifespan = 0.2f;
		m_scene->Add(std::move(emitter));

	}
}
