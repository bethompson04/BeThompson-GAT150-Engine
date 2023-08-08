#pragma once
#include "Core/Vector2.h"
#include "Core/Color.h"
#include <vector>

namespace MEN
{
    class Renderer;

    struct ParticleData
    {
        vec2 position;
        vec2 prevPosition;
        vec2 velocity;
        float damping = 0;

        Color color;

        float lifeTimer = 0;
        float lifeTime = 0;
    };

    class Particle
    {
    public:
        Particle() = default;

        void Initialize(const ParticleData& data)
        {
            m_data = data;
            m_isActive = true;
        }

        void Update(float deltaTime);
        void Draw(Renderer& renderer);

        friend class ParticleSystem;

    private:
        ParticleData m_data;
        bool m_isActive = false;
    };
}