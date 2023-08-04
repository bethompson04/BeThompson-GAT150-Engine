#pragma once
#include "Resource.h"
#include <map>
#include <memory>
#include <string>

namespace MEN
{
	class ResourceManager
	{

	public:
		template<typename T,typename ... TArgs>
		res_t<T> Get(const std::string& fileName, TArgs ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};

	template<typename T, typename ...TArgs>
	inline res_t<T> ResourceManager::Get(const std::string& fileName, TArgs ...args)
	{
		if (m_resources.find(fileName) != m_resources.end())
		{
			return std::dynamic_pointer_cast<T>(m_resources[fileName]);
		}

		res_t<T> resource = std::make_shared<T>();
		resource->Create(fileName, args...);

		m_resources[fileName] = resource;

		return resource;
	}

	extern ResourceManager g_resourceManager;
}