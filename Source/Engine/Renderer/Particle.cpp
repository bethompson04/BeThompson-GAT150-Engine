#include "Particle.h"

namespace MEN
{
    void MEN::Particle::Update(float deltaTime)
    {
        m_data.lifeTimer += deltaTime;
        if (m_data.lifeTimer >= m_data.lifeTime)
        {
            m_isActive = false;
            return;
        }

        m_data.prevPosition = m_data.position;
        m_data.position += m_data.velocity * deltaTime;
        m_data.velocity *= std::pow(1.0f - m_data.damping, deltaTime);

    }

    void MEN::Particle::Draw(Renderer& renderer)
    {
        renderer.SetColor(Color::ToInt(m_data.color.r), Color::ToInt(m_data.color.g), Color::ToInt(m_data.color.b), Color::ToInt(m_data.color.a));
        renderer.DrawLine(m_data.position.x, m_data.position.y, m_data.prevPosition.x, m_data.prevPosition.y);
    }
}