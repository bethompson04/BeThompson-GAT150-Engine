#include "SpriteComponent.h"
#include "Renderer/Renderer.h"
#include "Framework/Actor.h"

namespace MEN
{
	void SpriteComponent::Update(float deltaTime)
	{

	}

	void SpriteComponent::Draw(Renderer& renderer)
	{
		renderer.DrawTexture(m_texture.get(), m_owner->m_Transform.position.x, m_owner->m_Transform.position.y, RadiansToDegrees(m_owner->m_Transform.rotation));
	}
}
