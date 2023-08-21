
#pragma once
#include "Framework/Actor.h"
#include <string>


namespace MEN
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon);
		//Weapon(std::string pewSound, float speed, const MEN::Transform& transform) :
		//	m_weaponSound{ pewSound },
		//	m_speed{ speed },
		//	Actor(transform)
		//{
		//	lifespan = 2.0f;
		//}

		bool Initialize() override;
		void Update(float deltaTime) override;
		void OnCollision(Actor* other);

	private:
		float speed = 0;
		std::string m_weaponSound;
	};
}