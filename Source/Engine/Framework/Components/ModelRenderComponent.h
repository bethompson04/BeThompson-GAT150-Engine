#pragma once
#include "RenderComponent.h"
#include "Renderer/Model.h"

namespace MEN
{
	class ModelRenderComponent : public RenderComponent
	{
	public:
		CLASS_DECLARATION(ModelRenderComponent)

		bool Initialize() override;

		void Update(float deltaTime) override;
		void Draw(class Renderer& renderer) override;

		virtual float GetRadius() override { return m_model->getRadius(); }

	public:
		std::string modelName;
		res_t<Model> m_model;
	};
}