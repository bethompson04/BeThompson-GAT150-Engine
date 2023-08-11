#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include "Framework/Object.h"
#include <memory>

namespace MEN
{
	class Actor : public Object
	{
	public:
		Actor() = default;

		Actor(const Transform& transform) :
			m_Transform{ transform }
		{}

		virtual bool Initialize() override;
		virtual void OnDestroy() override;

		virtual void Update(float deltaTime);
		virtual void Draw(MEN::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		float GetRadius() { return 30.0f; }
		virtual void OnCollision(Actor* other) {}

		friend class Scene;

		class Scene* m_scene = nullptr;

		class Game* m_game = nullptr;

		MEN::Transform m_Transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

		bool m_destroyed = false;
	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}
