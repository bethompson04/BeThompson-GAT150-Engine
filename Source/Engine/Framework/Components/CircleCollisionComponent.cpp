#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace MEN
{
    void MEN::CircleCollisionComponent::Update(float deltaTime)
    {

    }

    bool MEN::CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->m_Transform.position.Distance(collision->m_owner->m_Transform.position);
        float radius = m_radius + collision->m_radius;

        return (distance <= radius);
    }
}
