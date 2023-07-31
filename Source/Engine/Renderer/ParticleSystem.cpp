#include "ParticleSystem.h"

namespace MEN
{
    ParticleSystem g_particleSystem{ 10000 };

    // Particle System
    void ParticleSystem::Update(float deltaTime)
    {
        for (auto& particle : m_particles)
        {
            if (particle.m_isActive) particle.Update(deltaTime);
        }
    }

    void ParticleSystem::Draw(Renderer& renderer)
    {
        for (auto& particle : m_particles)
        {
            if (particle.m_isActive) particle.Draw(renderer);
        }
    }

    Particle* ParticleSystem::GetFreeParticle()
    {
        for (auto& particle : m_particles)
        {
            if (!particle.m_isActive) return &particle;
        }
        return nullptr;
    }

}
