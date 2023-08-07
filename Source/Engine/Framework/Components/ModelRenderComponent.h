#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace MEN
{
	class ModelRenderComponent : public RenderComponent
	{
	public:

		void Update(float deltaTime) override;
		void Draw(class Renderer& renderer) override;

	public:
		//res_t<Model> m_texture;
	};
}