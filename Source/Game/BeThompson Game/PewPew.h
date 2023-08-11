
#pragma once
#include "Framework/Actor.h"
#include <string>

class PewPew : public MEN::Actor
{
public:
	PewPew(std::string pewSound, float speed, const MEN::Transform& transform) :
		m_weaponSound{ pewSound },
		m_speed{ speed },
		Actor(transform)
	{
		m_lifespan = 2.0f;
	}
	bool Initialize() override;

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;


private:
	float m_speed = 0;
	std::string m_weaponSound;
};