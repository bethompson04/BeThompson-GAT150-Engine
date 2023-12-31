
#pragma once
#include "Framework/Actor.h"
#include <string>


namespace MEN
{
	class Weapon : public Actor
	{
	public:
		CLASS_DECLARATION(Weapon)

		bool Initialize() override;
		void Update(float deltaTime) override;

		void OnCollision(Actor* other);

	private:
		float speed = 0;
		std::string m_weaponSound;
		PhysicsComponent* m_physicsComponent = nullptr;
	};
}