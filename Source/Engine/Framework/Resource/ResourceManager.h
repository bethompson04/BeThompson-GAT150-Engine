#pragma once
#include "Resource.h"
#include "Framework/Singleton.h"
#include <map>
#include <memory>
#include <string>

#define GET_RESOURCE(type, fileName, ...) MEN::ResourceManager::Instance().Get<type>(fileName, __VA_ARGS__)

namespace MEN
{
	class ResourceManager : public Singleton<ResourceManager>
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
		// Find resource in resource manager
		if (m_resources.find(fileName) != m_resources.end())
		{
			// return resource
			return std::dynamic_pointer_cast<T>(m_resources[fileName]);
		}

		// resource not in resource manager, create resource
		res_t<T> resource = std::make_shared<T>();
		if (!resource->Create(fileName, args...))
		{
			// resource not created
			WARNING_LOG("Could not create resource: " << fileName);
			return res_t<T>();
		}

		// add resource to resrouce manager, return resource
		m_resources[fileName] = resource;
		return resource;

		resource = std::make_shared<T>();
		resource->Create(fileName, args...);

		m_resources[fileName] = resource;

		return resource;
	}

}