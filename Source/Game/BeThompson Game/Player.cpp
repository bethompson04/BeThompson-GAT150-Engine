#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "PewPew.h"
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
			float scale = m_Transform.scale;
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
	m_Transform.rotation += rotate * m_turnRate * MEN::g_time.GetDeltaTime();

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(m_Transform.rotation);


	m_physicsComponent->ApplyForce(forward * m_speed * thrust);

	m_Transform.position += forward * m_speed * thrust * MEN::g_time.GetDeltaTime();

	// - WRAPPING

	m_Transform.position.x = MEN::Wrap(m_Transform.position.x, (float)MEN::g_renderer.GetWidth());
	m_Transform.position.y = MEN::Wrap(m_Transform.position.y, (float)MEN::g_renderer.GetHeight());

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
	if (other->m_tag == "Rock")
	{
		this->m_destroyed = true;
		dynamic_cast<PewGame*>(m_game)->SetState(PewGame::eState::PlayerDeadStart);
	}
	
	if (other->m_tag == "Enemy" || other->m_tag == "Enemy_Bullet")
	{
		this->m_destroyed = true;
		other->m_destroyed = true;
		dynamic_cast<PewGame*>(m_game)->SetState(PewGame::eState::PlayerDeadStart);
	}	
}

void Player::Shoot(int score) {

	MEN::EmitterData data;

	data.burst = false;
	data.burstCount = 0;
	data.spawnRate = 100;
	data.angle = m_Transform.rotation;
	data.angleRange = MEN::pi / 4;
	data.lifeTimeMin = 0.6f;
	data.lifeTimeMax = 1.5f;
	data.speedMin = 250;
	data.speedMax = 500;
	data.damping = 0.9f;

	data.color = MEN::Color{ 0, 1, 0, 1 };

	MEN::Transform transformP{ { m_Transform.position }, 0, 1 };
	std::unique_ptr<MEN::Emitter> emitter = std::make_unique<MEN::Emitter>(transformP, data);
	emitter->m_lifespan = 0.1f;
	m_scene->Add(std::move(emitter));



	if(score >= 750 && score < 1500)
	{
		MEN::Transform transform2 {m_Transform.position, m_Transform.rotation + MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew2 = std::make_unique<PewPew>("pew", 400.0f, transform2);
		pewPew2->m_tag = "Player_Bullet";

		std::unique_ptr<MEN::SpriteComponent> component2 = std::make_unique<MEN::SpriteComponent>();
		component2->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);
		pewPew2->AddComponent(std::move(component2));

		auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		pewPew2->AddComponent(std::move(collisionComponent));

		m_scene->Add(std::move(pewPew2));

		MEN::Transform transform3 {m_Transform.position, m_Transform.rotation - MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew3 = std::make_unique<PewPew>("pew", 400.0f, transform3);
		pewPew3->m_tag = "Player_Bullet";

		std::unique_ptr<MEN::SpriteComponent> component3 = std::make_unique<MEN::SpriteComponent>();
		component3->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);
		

		auto collisionComponent2 = std::make_unique<MEN::CircleCollisionComponent>();
		collisionComponent2->m_radius = 30.0f;
		pewPew3->AddComponent(std::move(component3));
		pewPew3->AddComponent(std::move(collisionComponent2));

		m_scene->Add(std::move(pewPew3));
	}else if (score >= 1500)
	{
		MEN::Transform transform1{ m_Transform.position, m_Transform.rotation, 1 };
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, transform1);
		pewPew->m_tag = "Player_Bullet";

		std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
		component->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);

		pewPew->AddComponent(std::move(component));

		auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		pewPew->AddComponent(std::move(collisionComponent));

		m_scene->Add(std::move(pewPew));

		MEN::Transform transform2 {m_Transform.position, m_Transform.rotation + MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew2 = std::make_unique<PewPew>("pew", 400.0f, transform2);
		pewPew2->m_tag = "Player_Bullet";

		std::unique_ptr<MEN::SpriteComponent> component2 = std::make_unique<MEN::SpriteComponent>();
		component2->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);

		pewPew2->AddComponent(std::move(component2));

		auto collisionComponent2 = std::make_unique<MEN::CircleCollisionComponent>();
		collisionComponent2->m_radius = 30.0f;
		pewPew2->AddComponent(std::move(collisionComponent2));

		m_scene->Add(std::move(pewPew2));

		MEN::Transform transform3 {m_Transform.position, m_Transform.rotation - MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew3 = std::make_unique<PewPew>("pew", 400.0f, transform3);
		pewPew3->m_tag = "Player_Bullet";

		std::unique_ptr<MEN::SpriteComponent> component3 = std::make_unique<MEN::SpriteComponent>();
		component3->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);
		pewPew3->AddComponent(std::move(component3));

		auto collisionComponent3 = std::make_unique<MEN::CircleCollisionComponent>();
		collisionComponent3->m_radius = 30.0f;
		pewPew3->AddComponent(std::move(collisionComponent3));

		m_scene->Add(std::move(pewPew3));
	}else
	{
		MEN::Transform transform1{ m_Transform.position, m_Transform.rotation, 1 };
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, transform1);
		pewPew->m_tag = "Player_Bullet";

		std::unique_ptr<MEN::SpriteComponent> component = std::make_unique<MEN::SpriteComponent>();
		component->m_texture = MEN::g_resourceManager.Get<MEN::Texture>("rocket.png", MEN::g_renderer);
		pewPew->AddComponent(std::move(component));

		auto collisionComponent = std::make_unique<MEN::CircleCollisionComponent>();
		collisionComponent->m_radius = 30.0f;
		pewPew->AddComponent(std::move(collisionComponent));

		m_scene->Add(std::move(pewPew));
	}
}