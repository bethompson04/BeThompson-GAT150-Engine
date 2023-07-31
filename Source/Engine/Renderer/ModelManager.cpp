#include "ModelManager.h"

namespace MEN
{
	ModelManager g_mManager;

	std::shared_ptr<Model> MEN::ModelManager::Get(const std::string& fileName)
	{
		if (m_models.find(fileName) == m_models.end())
		{
			std::shared_ptr<Model> model = std::make_shared<Model>();
			model->Load(fileName);

			m_models[fileName] = model;
		}

		return m_models[fileName];
	}

}
