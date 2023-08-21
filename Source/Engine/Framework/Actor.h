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
		CLASS_DECLARATION(Actor)

		Actor() = default;

		Actor(const Transform& transform) :
			transform{ transform }
		{}

		Actor(const Actor& other);

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

		MEN::Transform transform;
		std::string tag;

		float lifespan = -1.0f;
		bool m_destroyed = false;
		bool persistent = false;
		bool prototype = false;

	protected:
		std::vector<std::unique_ptr<Component>> components;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}
