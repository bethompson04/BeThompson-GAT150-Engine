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
	AddForce(forward * m_speed * thrust);

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
		std::unique_ptr<PewPew> pewPew2 = std::make_unique<PewPew>("pew", 400.0f, transform2, MEN::g_mManager.Get("Laser.txt"));
		pewPew2->m_tag = "Player_Bullet";
		m_scene->Add(std::move(pewPew2));

		MEN::Transform transform3 {m_Transform.position, m_Transform.rotation - MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew3 = std::make_unique<PewPew>("pew", 400.0f, transform3, MEN::g_mManager.Get("Laser.txt"));
		pewPew3->m_tag = "Player_Bullet";
		m_scene->Add(std::move(pewPew3));
	}else if (score >= 1500)
	{
		MEN::Transform transform1{ m_Transform.position, m_Transform.rotation, 1 };
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, transform1, MEN::g_mManager.Get("Laser.txt"));
		pewPew->m_tag = "Player_Bullet";
		m_scene->Add(std::move(pewPew));

		MEN::Transform transform2 {m_Transform.position, m_Transform.rotation + MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew2 = std::make_unique<PewPew>("pew", 400.0f, transform2, MEN::g_mManager.Get("Laser.txt"));
		pewPew2->m_tag = "Player_Bullet";
		m_scene->Add(std::move(pewPew2));

		MEN::Transform transform3 {m_Transform.position, m_Transform.rotation - MEN::DegreesToRadians(20), 1};
		std::unique_ptr<PewPew> pewPew3 = std::make_unique<PewPew>("pew", 400.0f, transform3, MEN::g_mManager.Get("Laser.txt"));
		pewPew3->m_tag = "Player_Bullet";
		m_scene->Add(std::move(pewPew3));
	}else
	{
		MEN::Transform transform1{ m_Transform.position, m_Transform.rotation, 1 };
		std::unique_ptr<PewPew> pewPew = std::make_unique<PewPew>("pew", 400.0f, transform1, MEN::g_mManager.Get("Laser.txt"));
		pewPew->m_tag = "Player_Bullet";
		m_scene->Add(std::move(pewPew));
	}
}