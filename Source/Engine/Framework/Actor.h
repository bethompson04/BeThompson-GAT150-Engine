#pragma once
#include "Core/Core.h"
#include "Renderer/Model.h"
#include "Components/Component.h"
#include <memory>

namespace MEN
{
	class Actor
	{
	public:
		Actor() = default;
		Actor(const MEN::Transform transform, std::shared_ptr<Model> model) : m_Transform{ transform }, m_model{model}
		{}

		Actor(const Transform& transform) :
			m_Transform{ transform }
		{}

		virtual void Update(float deltaTime);
		virtual void Draw(MEN::Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		float GetRadius() { return (m_model) ? m_model->getRadius() * m_Transform.scale : 0; }
		virtual void OnCollision(Actor* other) {}

		void AddForce(const vec2 force) { m_velocity += force; }
		void SetDamping(float damping) { m_damping = damping; }

		friend class Scene;

		class Scene* m_scene = nullptr;

		class Game* m_game = nullptr;

		MEN::Transform m_Transform;
		std::string m_tag;

		float m_lifespan = -1.0f;

		bool m_destroyed = false;
	protected:
		std::vector<std::unique_ptr<Component>> m_components;

		std::shared_ptr<Model> m_model;

		vec2 m_velocity;
		float m_damping = 0;
	};
}
