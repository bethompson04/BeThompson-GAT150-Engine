#pragma once
#include "Core/Vector2.h"

struct SDL_Texture;

namespace MEN
{
	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(class Renderer& renderer, const std::string& fileName);
		vec2 GetSize();

		friend class Renderer;
	private:
		SDL_Texture* m_texture = nullptr;
	};
}