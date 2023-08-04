#pragma once
#include "Framework/Components/RenderComponent.h"
#include "Renderer/Texture.h"
namespace MEN
{
	class SpriteComponent : public RenderComponent
	{
	public:

		void Update(float deltaTime) override;
		void Draw(class Renderer& renderer) override;

	public:
		res_t<Texture> m_texture;
	};
}