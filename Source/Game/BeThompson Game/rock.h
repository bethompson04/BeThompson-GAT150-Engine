#pragma once
#include "Framework/Actor.h"

class Rock : public MEN::Actor
{
public:
	Rock(float speed, const MEN::Transform& transform) :
		Actor(transform), m_speed{ speed }
	{
	}

	void Update(float deltaTime) override;
	void OnCollisionEnter(Actor* other) override;

protected:
	float m_speed = 0;
};