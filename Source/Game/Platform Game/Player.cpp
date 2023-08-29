#include "Player.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/ModelManager.h"
#include "Audio/AudioSystem.h"
#include "Renderer/Texture.h"


#include "Framework/Framework.h"

namespace MEN
{
	CLASS_DEFINITION(Player)

		bool Player::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<MEN::PhysicsComponent>();
		m_spriteAnimComponent = GetComponent<SpriteAnimComponent>();

		return true;
	}

	void Player::Update(float deltaTime)
	{
		Actor::Update(deltaTime);

		bool onGround = (groundCount > 0);

		// - MOVEMENT

		float direction = 0;

		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction = -1;
		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction = 1;

		MEN::vec2 forward = MEN::vec2{ 1 , 0 };



		m_physicsComponent->ApplyForce(forward * speed * direction * ((onGround) ? 1 : 0.0001f));

		// - WRAPPING
		// Jump


		if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !MEN::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE) && onGround)
		{
			MEN::vec2 up = MEN::vec2{ 0 , -1 };
			m_physicsComponent->SetVelocity(up * jump);
		}

		


		// Animation
		vec2 velocity = m_physicsComponent->m_velocity;
		// check if moving
		if (std::fabs(velocity.x) > 0.2f)
		{
			if (direction != 0) m_spriteAnimComponent->flipH = (direction < 0);
			m_spriteAnimComponent->SetSequence("run");
		}
		else 
		{
			m_spriteAnimComponent->SetSequence("idle");
		}


	}

	void Player::OnCollisionEnter(Actor* other)
	{

		if (other->tag == "Enemy")
		{
			//this->m_destroyed = true;
			//other->m_destroyed = true;
			//MEN::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}

		if (other->tag == "Ground") groundCount++;

	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount;

	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, jump);
	}
}