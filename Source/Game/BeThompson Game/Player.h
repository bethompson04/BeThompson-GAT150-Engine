#pragma once
#include "Framework/Actor.h"

class Player : public MEN::Actor
{
public:
	Player(float speed, float turnRate, const MEN::Transform& transform) :
		Actor(transform), m_speed{speed}, m_turnRate {turnRate}
	{}

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	bool multiShotx2 = false;
		bool multiShotx3 = false;
	
	void Shoot(int score);
};