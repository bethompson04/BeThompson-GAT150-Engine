#pragma once

#include <list>
#include "Actor.h"

namespace MEN
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;
		~Scene() = default;

		bool Initialize();
		void Update(float deltaTime);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& fileName);
		void Read(const json_t& value);

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);


		friend class Actor;

		std::list<std::unique_ptr<Actor>> m_actors;
	private:
	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*> (actor.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor->name == name)
			{
				T* result = dynamic_cast<T*> (actor.get());
				if (result) return result;
			}
		}

		return nullptr;
	}
}