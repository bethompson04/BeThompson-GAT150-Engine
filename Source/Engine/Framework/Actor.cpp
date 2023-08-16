#include "Actor.h"
#include "Components/RenderComponent.h"

namespace MEN
{
	CLASS_DEFINITION(Actor)

	bool Actor::Initialize()
	{
		for (auto& component : components)
		{
			component->Initialize();
		}

		return true;
	}

	void Actor::OnDestroy()
	{
		for (auto& component : components)
		{
			component->OnDestroy();
		}
	}
	void Actor::Update(float deltaTime)
	{
		if (lifespan != -1.0f)
		{
			lifespan -= deltaTime;
			m_destroyed = (lifespan <= 0.0f);
		}

		for (auto& component : components)
		{
			component->Update(deltaTime);
		}

	}

	void Actor::Draw(MEN::Renderer& renderer)
	{
		//m_model->Draw(renderer, m_Transform);
		for (auto& component : components)
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
		components.push_back(std::move(component));
	}

	void Actor::Read(const json_t& value)
	{
		Object::Read(value);

		READ_DATA(value, tag);
		READ_DATA(value, lifespan);

		if (HAS_DATA(value, transform)) transform.Read(value);

		if (HAS_DATA(value, components) && GET_DATA(value, components).IsArray())
		{
			for (auto& componentValue : GET_DATA(value, components).GetArray())
			{
				std::string type;
				READ_DATA(componentValue, type);

				auto component = CREATE_CLASS_BASE(Component, type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}

}
