#pragma once
#include <string>
#include <Framework/Resource/Resource.h>

struct _TTF_Font;

namespace MEN
{
	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		virtual bool Create(std::string fileName, ...) override;
		bool Load(const std::string& filename, int fontSize);

		friend class Text;

	private:
		_TTF_Font* m_ttfFont = nullptr;

	};
}