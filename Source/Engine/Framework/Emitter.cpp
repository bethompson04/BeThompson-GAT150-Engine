#include "Emitter.h"

namespace MEN
{
    void Emitter::Update(float deltaTime)
    {
        Actor::Update(deltaTime);

        // create burst particles
        if (m_data.burst)
        {
            m_data.burst = false;
            for (int i = 0; i < m_data.burstCount; i++)
            {
                Emit();
            }
        }

        // Create particles based on rate
        if (m_data.spawnRate > 0.0f)
        {
            m_data.spawnRateTimer += deltaTime;
            while (m_data.spawnRateTimer > 0)
            {
                Emit();
                m_data.spawnRateTimer -= (1 / m_data.spawnRate);
            }
        }
    }

    void Emitter::Draw(Renderer& renderer)
    {
        //
    }

    void Emitter::Emit()
    {
        Particle* particle = g_particleSystem.GetFreeParticle();

        if (particle)
        {
            ParticleData data;
            data.lifeTime = randomf(m_data.lifeTimeMin, m_data.lifeTimeMax);
            data.lifeTimer = 0.0f;
            data.position = m_Transform.position;
            data.prevPosition = data.position;
            data.color = m_data.color;

            float angle = m_Transform.rotation + m_data.angle + randomf(-m_data.angleRange, m_data.angleRange);
            vec2 direction = vec2{ 0,-1 }.Rotate(angle);
            data.velocity = direction * randomf(m_data.speedMin, m_data.speedMax);
            data.damping = m_data.damping;

            particle->Initialize(data);
        }
    }
}