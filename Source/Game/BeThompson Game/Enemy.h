#pragma once
#include "Framework/Actor.h"

class Enemy : public MEN::Actor
{
public:
	Enemy(float speed, float turnRate, const MEN::Transform& transform) :
		Actor(transform),
		m_speed{ speed },
		m_turnRate{ turnRate }
	{
		m_fireRate = 2.0f;
		m_fireTimer = m_fireRate;
	}
	virtual bool Initialize() override;

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
	float m_turnRate = 0;

	float m_fireRate = 0;
	float m_fireTimer = 0;

	
};