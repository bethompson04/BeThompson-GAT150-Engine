
#pragma once
#include "Framework/Actor.h"
#include <string>

class PewPew : public MEN::Actor
{
public:
	PewPew(std::string pewSound, float speed, const MEN::Transform& transform, const std::shared_ptr<MEN::Model> model) :
		Actor(transform, model), m_speed{ speed }, m_weaponSound{pewSound}
	{
		m_lifespan = 2.0f;
	}

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	std::string m_weaponSound;
};