#pragma once

namespace MEN
{
	class Component
	{
	public:
		
		virtual void Update(float deltaTime) = 0;

		friend class Actor;
	protected:
		Actor* m_owner = nullptr;
	};
}