#pragma once
#include "Framework/Actor.h"

class Rock : public MEN::Actor
{
public:
	Rock(float speed, const MEN::Transform& transform, const std::shared_ptr<MEN::Model> model) :
		Actor(transform, model), m_speed{ speed }
	{
	}

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;

protected:
	float m_speed = 0;
};