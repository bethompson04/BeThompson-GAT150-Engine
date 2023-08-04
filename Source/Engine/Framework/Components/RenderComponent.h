#pragma once
#include "Component.h"

namespace MEN
{
	class RenderComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}