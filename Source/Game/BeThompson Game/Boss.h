#pragma once
#include "Enemy.h"

class Boss : public Enemy
{
public:

	Boss(int HP, float speed, float turnRate, const MEN::Transform& transform, const std::shared_ptr<MEN::Model> model) :
		Enemy{ speed, turnRate, transform, model }
	{
		m_fireRate = 1.0f;
		m_fireTimer = m_fireRate;
		hits = 0;;
	}

	void Update(float deltaTime) override;
	void OnCollision(Actor* other);

	int hits;

private:
	int hitsToDie;

	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;
};