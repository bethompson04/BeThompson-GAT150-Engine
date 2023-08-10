#include "ModelRenderComponent.h"
#include "Framework/Actor.h"

namespace MEN
{
	void ModelRenderComponent::Update(float deltaTime)
	{

	}

	void ModelRenderComponent::Draw(Renderer& renderer)
	{
		m_model->Draw(renderer, m_owner->m_Transform);
	}

}
