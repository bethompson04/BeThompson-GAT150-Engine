
#pragma once
#include "Framework/Components/Component.h"
#include <string>


namespace MEN
{
	class PewComponent : public MEN::Component
	{
	//public:
	//	PewPew(std::string pewSound, float speed, const MEN::Transform& transform) :
	//		m_weaponSound{ pewSound },
	//		m_speed{ speed },
	//		Actor(transform)
	//	{
	//		lifespan = 2.0f;
	//	}

		bool Initialize() override;
		void Update(float deltaTime) override;
		void OnCollision(Actor* other);
		void Read(const json_t& value);


	private:
		float speed = 0;
		std::string m_weaponSound;
	};
}