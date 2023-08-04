#include "Font.h"
#include <SDL2-2.28.0/include/SDL_ttf.h>
#include "Core/Logger.h"
namespace MEN
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont != nullptr) TTF_CloseFont(m_ttfFont);
	}

	bool Font::Create(std::string fileName, ...)
	{
		va_list args;

		va_start(args, fileName);

		int fontSize = va_arg(args, int);

		va_end(args);

		return Load(fileName, fontSize);
	}

	bool Font::Load(const std::string& filename, int fontSize)
	{
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);

		if (m_ttfFont == nullptr) // (!m_ttfFont)
		{
			WARNING_LOG("Failed to open font: " << filename);
			return false;
		}
		return true;
	}
}