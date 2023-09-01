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
		vec2 velocity = m_physicsComponent->m_velocity;

		// - MOVEMENT
		direction = 0;
		if ((pState == playerState::REST) || (pState == playerState::JUMP))
		{
			if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction = -1;
			if (MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction = 1;
			if (direction)
			{
				velocity.x += speed * direction * ((onGround) ? 1 : 0.5f) * deltaTime;
				velocity.x = Clamp(velocity.x, -maxSpeed, maxSpeed);
				m_physicsComponent->SetVelocity(velocity);
				tempDir = direction;
			}

		}

		// Jump

		switch (pState)
		{
		case playerState::REST:
		{
			attackTimer = 0;
			attackType = 1;

			// Input Checks (Jump, Roll, Attack)
			// Jump Check
			if (onGround && MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_W) && !MEN::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_W))
			{
				MEN::vec2 up = MEN::vec2{ 0 , -1 };
				m_physicsComponent->SetVelocity(velocity + (up * jump));

				pState = playerState::JUMP;
				break;
			}

			// Roll Check
			if (onGround && direction && MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_LSHIFT) && !MEN::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_LSHIFT))
			{
				pState = playerState::ROLL;
				tempDir = direction;
				break;
			}

			// Attack Check
			if (onGround && MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				pState = playerState::ATTACK;
				break;
			}

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
			break;
		}
		case playerState::JUMP:
		{
			m_physicsComponent->SetGravityScale((velocity.y > 0) ? 1.75 : 1);

			if (!onGround)
			{
				if (velocity.y > 0)
				{
					m_spriteAnimComponent->SetSequence("fall");
				}
				else if (velocity.y < 0)
				{
					m_spriteAnimComponent->SetSequence("jump");
				}
			}

			if (velocity.y == 0 && onGround)
			{
				pState = playerState::REST;
			}

			break;
		}
		case playerState::ROLL:
		{
			if (attackTimer == 0)
			{
				m_physicsComponent->ApplyForce({750.0f * tempDir, 0.0f });
			}

			attackTimer += deltaTime;

			if (attackTimer <= 1)
			{
				m_spriteAnimComponent->SetSequence("roll");
			}
			else
			{
				pState = playerState::REST;
			}
			break;
		}
		case playerState::ATTACK:
		{
			m_physicsComponent->SetVelocity(0);

			attackTimer += deltaTime;

			if (attackType == 1 && attackTimer <= 0.3)
			{
				m_spriteAnimComponent->SetSequence("attack1");
				MEN::g_audioSystem.PlayOneShot("attack");

			}else if (attackTimer <= 1 && MEN::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
			{
				m_spriteAnimComponent->SetSequence("attack2");
				MEN::g_audioSystem.PlayOneShot("attack");
			}
			else
			{
				pState = playerState::REST;
			}


			break;
		}
		case playerState::DEAD:
		{
			break;
		}
		}

	}

	void Player::OnCollisionEnter(Actor* other)
	{

		if (other->tag == "Enemy" || other->tag == "spike")
		{
			this->m_destroyed = true;
			//other->m_destroyed = true;
			MEN::EventManager::Instance().DispatchEvent("OnPlayerDead", 0);
		}

		if (other->tag == "Ground") groundCount++;

		if (other->tag == "coin")
		{
			MEN::EventManager::Instance().DispatchEvent("OnAddPoints", 100);
			MEN::g_audioSystem.PlayOneShot("collect", false);
			other->m_destroyed = true;
		}

	}

	void Player::OnCollisionExit(Actor* other)
	{
		if (other->tag == "Ground") groundCount--;

	}

	void Player::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
		READ_DATA(value, maxSpeed);
		READ_DATA(value, jump);
	}
}