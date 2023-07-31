#pragma once
#include "Framework/Actor.h"

class Player : public MEN::Actor
{
public:
	Player(float speed, float turnRate, const MEN::Transform& transform, std::shared_ptr<MEN::Model> model) :
		Actor(transform, model), m_speed{speed}, m_turnRate {turnRate}
	{}

	void Update(float deltaTime) override;
	void OnCollision(Actor* other) override;

private:
	float m_speed = 0;
	float m_turnRate = 0;

	bool multiShotx2;
	bool multiShotx3;
	
	void Shoot(int score);
};