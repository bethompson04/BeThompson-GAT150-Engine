#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Weapon.h"
#include "Framework/Scene.h"
#include "PewGame.h"
#include "Framework/Emitter.h"
#include "PewGame.h"
#include "Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Framework/Components/SpriteComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Resource/ResourceManager.h"

#include "Framework/Framework.h"

bool Player::Initialize()
{
	Actor::Initialize();

	// cache off
	m_physicsComponent = GetComponent<MEN::PhysicsComponent>();

	auto collisionComponent = GetComponent<MEN::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<MEN::RenderComponent>();
		if (renderComponent)
		{
			float scale = transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale * 0.75f;

		}
	}

	return true;
}

void Player::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	// - MOVEMENT

	float rotate = 0;
	float thrust = 0;
	if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;
	if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) thrust = 0;
	if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	transform.rotation += rotate * m_turnRate * MEN::g_time.GetDeltaTime();

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(transform.rotation);


	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	transform.position += forward * m_speed * thrust * MEN::g_time.GetDeltaTime();

	// - WRAPPING

	transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
	transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());

	// Fire the PewPew
	if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !MEN::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		MEN::g_audioSystem.PlayOneShot("pew", false);
		Shoot(m_game->GetScore());
		
	}

	if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) MEN::g_time.SetTimeScale(0.5f);
	else MEN::g_time.SetTimeScale(1.0f);

}

void Player::OnCollision(Actor* other)
{
	if (other->tag == "Rock")
	{
		this->m_destroyed = true;
		MEN::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
	}
	
	if (other->tag == "Enemy" || other->tag == "Enemy_Bullet")
	{
		this->m_destroyed = true;
		other->m_destroyed = true;
		MEN::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		
	}	
}

void Player::Shoot(int score) {

	MEN::EmitterData data;

	data.burst = false;
	data.burstCount = 0;
	data.spawnRate = 100;
	data.angle = transform.rotation;
	data.angleRange = MEN::pi / 4;
	data.lifeTimeMin = 0.6f;
	data.lifeTimeMax = 1.5f;
	data.speedMin = 250;
	data.speedMax = 500;
	data.damping = 0.9f;

	data.color = MEN::Color{ 0, 1, 0, 1 };

	MEN::Transform transformP{ { transform.position }, 0, 1 };
	std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
	emitter->lifespan = 0.1f;
	m_scene->Add(std::move(emitter));




	if(score >= 750 && score < 1500)
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket_Player");
		weapon->transform = { transform.position, transform.rotation + MEN::DegreesToRadians(20), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		weapon = INSTANTIATE(Weapon, "Rocket_Player");
		weapon->transform = { transform.position, transform.rotation - MEN::DegreesToRadians(20), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	}else if (score >= 1500)
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket_Player");
		weapon->transform = { transform.position, transform.rotation + MEN::DegreesToRadians(20), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		weapon = INSTANTIATE(Weapon, "Rocket_Player");
		weapon->transform = { transform.position, transform.rotation - MEN::DegreesToRadians(20), 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));

		weapon = INSTANTIATE(Weapon, "Rocket_Player");
		weapon->transform = { transform.position, transform.rotation, 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	}else
	{
		auto weapon = INSTANTIATE(Weapon, "Rocket_Player");
		weapon->transform = { transform.position, transform.rotation, 1 };
		weapon->Initialize();
		m_scene->Add(std::move(weapon));
	}
}