#include "Weapon.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace MEN
{
	CLASS_DEFINITION(Weapon);

	bool Weapon::Initialize()
	{
		Actor::Initialize();

		m_physicsComponent = GetComponent<PhysicsComponent>();

		auto collisionComponent = GetComponent<CollisionComponent>();
		if (collisionComponent)
		{

		}
		return true;
	}

	void Weapon::Update(float deltaTime)
	{
		Actor::Update(deltaTime);

		MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(transform.rotation);
		m_physicsComponent->SetVelocity(forward * speed);

		transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
		transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());
	}

	void Weapon::Read(const json_t& value)
	{
		Actor::Read(value);

		READ_DATA(value, speed);
	}

	void Weapon::OnCollision(Actor* other)
	{
		if (other->tag != tag)
		{
			m_destroyed = true;
		}
	}
}
