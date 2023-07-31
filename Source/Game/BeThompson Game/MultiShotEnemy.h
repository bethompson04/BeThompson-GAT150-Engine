#pragma once
#include "Enemy.h"
#include "Framework/Actor.h"

class MultiShotEnemy : public Enemy
{
public:
	MultiShotEnemy(float speed, float turnRate, const MEN::Transform& transform, const std::shared_ptr<MEN::Model> model) : Enemy{ speed, turnRate, transform, model }
	{
		m_fireRate = 5.0f;
		m_fireTimer = m_fireRate;
	}

	void Update(float deltaTime);
	void OnCollision(Actor* other);

	
private:
};