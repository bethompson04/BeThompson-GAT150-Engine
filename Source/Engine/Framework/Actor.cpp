#include "Actor.h"
#include "Components/RenderComponent.h"

namespace MEN
{
	void Actor::Update(float deltaTime)
	{
		if (m_lifespan != -1.0f)
		{
			m_lifespan -= deltaTime;
			m_destroyed = (m_lifespan <= 0.0f);
		}

		for (auto& component : m_components)
		{
			component->Update(deltaTime);
		}

	}

	void Actor::Draw(MEN::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_Transform);
		for (auto& component : m_components)
		{
			if (dynamic_cast<RenderComponent*>(component.get()))
			{
				dynamic_cast<RenderComponent*>(component.get())->Draw(renderer);
			}
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}

}
