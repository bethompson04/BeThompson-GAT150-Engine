#include "CircleCollisionComponent.h"
#include "Framework/Actor.h"

namespace MEN
{
    CLASS_DEFINITION(CircleCollisionComponent)

    void MEN::CircleCollisionComponent::Update(float deltaTime)
    {

    }

    bool MEN::CircleCollisionComponent::CheckCollision(CollisionComponent* collision)
    {
        float distance = m_owner->transform.position.Distance(collision->m_owner->transform.position);
        float radius = m_radius + collision->m_radius;

        return (distance <= radius);
    }

    void MEN::CircleCollisionComponent::Read(const json_t& value)
    {

    }
}
