#include "PewComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

namespace MEN
{
	bool PewComponent::Initialize()
	{
		auto collisionComponent =m_owner->GetComponent<MEN::CollisionComponent>();
		if (collisionComponent)
		{
			auto renderComponent = m_owner->GetComponent<MEN::RenderComponent>();
			if (renderComponent)
			{
				float scale = m_owner->transform.scale;
				collisionComponent->m_radius = renderComponent->GetRadius() * scale;

			}
		}
		return true;
	}

	void PewComponent::Update(float deltaTime)
	{
		Actor::Update(deltaTime);

		MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(m_owner->transform.rotation);

		m_owner->transform.position += forward * speed * MEN::g_time.GetDeltaTime();

		m_owner->transform.position.x = MEN::Wrap(m_owner->transform.position.x, (float)MEN::g_renderer.GetWidth());
		m_owner->transform.position.y = MEN::Wrap(m_owner->transform.position.y, (float)MEN::g_renderer.GetHeight());
	}

	void MEN::PewComponent::Read(const json_t& value)
	{
	}

	void PewComponent::OnCollision(Actor* other)
	{
		if (other->tag != m_owner->tag)
		{
			m_owner->m_destroyed = true;
		}
	}
}
