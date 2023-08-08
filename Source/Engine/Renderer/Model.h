#pragma once
#include "Core/Core.h"
#include <vector>
#include "Framework/Resource/Resource.h"

namespace MEN
{
	class Renderer;

	class Model: public Resource
	{
	public:
		Model() = default;
		Model(const std::vector<vec2>& points) : m_points{ points } {}
		
		virtual bool Create(std::string fileName, ...) override;

		bool Load(const std::string& fileName);
		void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
		void Draw(Renderer& renderer, const Transform& transform);

		float getRadius();

	private:
		std::vector<vec2> m_points;
		Color m_color;
		float m_radius = 0;

		// Inherited via Resource
	};
}