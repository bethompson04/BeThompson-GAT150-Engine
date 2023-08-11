#include "PewPew.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool PewPew::Initialize()
{
	auto collisionComponent = GetComponent<MEN::CollisionComponent>();
	if (collisionComponent)
	{
		auto renderComponent = GetComponent<MEN::RenderComponent>();
		if (renderComponent)
		{
			float scale = m_Transform.scale;
			collisionComponent->m_radius = renderComponent->GetRadius() * scale;

		}
	}
	return true;
}

void PewPew::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(m_Transform.rotation);

	m_Transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	m_Transform.position.x = MEN::Wrap(m_Transform.position.x, (float)MEN::g_renderer.GetWidth());
	m_Transform.position.y = MEN::Wrap(m_Transform.position.y, (float)MEN::g_renderer.GetHeight());
}

void PewPew::OnCollision(Actor* other)
{
	m_destroyed = true;
}
