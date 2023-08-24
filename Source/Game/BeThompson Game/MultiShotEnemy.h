#pragma once
#include "Enemy.h"
#include "Framework/Actor.h"

namespace MEN
{
	class MultiShotEnemy : public Enemy
	{
	public:
		CLASS_DECLARATION(MultiShotEnemy)

		MultiShotEnemy() = default;
		MultiShotEnemy(float speed, float turnRate, const MEN::Transform& transform) : Enemy{ speed, turnRate, transform }
		{
			m_fireRate = 5.0f;
			m_fireTimer = m_fireRate;
		}

		void Update(float deltaTime);
		void OnCollision(Actor* other);
	
	private:
	};
}