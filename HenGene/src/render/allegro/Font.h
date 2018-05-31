
#pragma once

#include "io/File.h"

#include <string>
#include <unordered_map>

struct ALLEGRO_FONT;

namespace render
{
	namespace allegro
	{
		class Font
		{
		public:
			Font() = default;
			Font(const Font &) = delete;
			Font(Font && other) noexcept;
			~Font();

			Font & operator=(const Font &) = delete;
			Font & operator=(Font && other) noexcept;

			bool load(const io::File & file);

			ALLEGRO_FONT * get(unsigned int size, unsigned int flags = 0u);

		private:
			io::File m_file{ "" };

			std::unordered_map<std::string, ALLEGRO_FONT*> m_handles;
		};
	}
}