#pragma once
#include "Framework/Components/RenderComponent.h"
#include "Renderer/Texture.h"
#include "Framework/Factory.h"

namespace MEN
{
	class SpriteComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(SpriteComponent)

		bool Initialize() override;
		void Update(float deltaTime) override;
		void Draw(class Renderer& renderer) override;

	public:
		Rect source;
		std::string textureName;
		res_t<Texture> m_texture;
	};
}