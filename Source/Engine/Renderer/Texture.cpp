#include "Texture.h"
#include "Renderer.h"
#include <cassert>
#include "Core/Logger.h"
#include "SDL2-2.28.0/include/SDL_image.h"

namespace MEN
{
	Texture::~Texture()
	{
		if (m_texture) SDL_DestroyTexture(m_texture);
	}

	bool Texture::Create(Renderer& renderer, const std::string& fileName)
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface)
		{
			WARNING_LOG("Image failed to load");
			return false;
		}

		m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
		SDL_FreeSurface(surface);
		if (!m_texture)
		{
			WARNING_LOG("Texture failed to load");
			return false;
		}
		return true;
	}

	vec2 Texture::GetSize()
	{
		ASSERT_LOG((this->m_texture != nullptr), "Texture is NULL");
		SDL_Point point;

		SDL_QueryTexture(this->m_texture, NULL, NULL, &point.x, &point.y);
		return vec2{ point.x, point.y };
	}
}