#include "Actor.h"

namespace MEN
{
	void Actor::Update(float deltaTime)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= deltaTime;
			m_destroyed = (m_lifespan <= 0.0f);
		}

		m_Transform.position += m_velocity * deltaTime;
		m_velocity *= std::pow(1 - m_damping, deltaTime);

	}

	void Actor::Draw(MEN::Renderer& renderer)
	{
		m_model->Draw(renderer, m_Transform);
	}

}
