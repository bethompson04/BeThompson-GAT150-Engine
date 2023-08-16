#include "rock.h"
#include "Renderer/Renderer.h"

void Rock::Update(float deltaTime)
{
	Actor::Update(deltaTime);

	MEN::vec2 forward = MEN::vec2{ 0 , -1 }.Rotate(transform.rotation);


	transform.position += forward * m_speed * MEN::g_time.GetDeltaTime();

	transform.position.x = MEN::Wrap(transform.position.x, (float)MEN::g_renderer.GetWidth());
	transform.position.y = MEN::Wrap(transform.position.y, (float)MEN::g_renderer.GetHeight());
}

void Rock::OnCollision(Actor* other)
{
}
