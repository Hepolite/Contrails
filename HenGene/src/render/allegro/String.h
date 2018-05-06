
#pragma once

#include "asset/AssetRef.h"
#include "render/allegro/Font.h"

#include <allegro5/color.h>
#include <allegro5/utf8.h>
#include <glm/vec2.hpp>
#include <string>

namespace render
{
	namespace allegro
	{
		class String
		{
		public:
			String() = delete;
			String(const std::string & str);
			String(const String & other) = delete;
			String(String && other) = delete;
			~String();

			String & operator=(const String & other) = delete;
			String & operator=(String && other) = delete;

			inline void setFont(const asset::Ref<Font> & font) { m_font = font; }
			inline void setSize(unsigned int size) { m_size = size; }
			inline void setFlags(unsigned int flags) { m_flags = flags; }
			inline void setColor(const ALLEGRO_COLOR & color) { m_color = color; }

			void draw(const glm::vec2 & pos) const;

		private:
			ALLEGRO_USTR * m_handle = nullptr;

			asset::Ref<Font> m_font;
			unsigned int m_size = 12u;
			unsigned int m_flags = 0u;
			ALLEGRO_COLOR m_color{ 1.0f, 1.0f, 1.0f, 1.0f };
		};
	}
}