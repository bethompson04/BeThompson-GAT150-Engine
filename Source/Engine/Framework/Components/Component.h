#pragma once
#include "Framework/Object.h"

namespace MEN
{
	class Component: public Object
	{
	public:
		
		virtual void Update(float deltaTime) = 0;

		friend class Actor;

	public:
		class Actor* m_owner = nullptr;
	};
}