
#pragma once

#include "asset/AssetRegistry.h"
#include "render/allegro/String.h"
#include "render/allegro/Text.h"

#include <allegro5/color.h>

namespace render
{
	namespace allegro
	{
		class TextBuilder
		{
		public:
			TextBuilder() = delete;
			TextBuilder(const asset::AssetRegistry & assets) : m_assets(assets) {}
			TextBuilder(const TextBuilder &) = delete;
			TextBuilder(TextBuilder &&) = delete;
			~TextBuilder() = default;

			TextBuilder & operator=(const TextBuilder &) = delete;
			TextBuilder & operator=(TextBuilder &&) = delete;

			inline auto empty() const { return m_text.empty(); }
			inline auto size() const { return m_text.size(); }

			inline void setFont(const std::string & font) { m_font = font; }
			inline void setSize(unsigned int size) { m_size = size; }
			inline void setColor(const ALLEGRO_COLOR & color) { m_color = color; }
			inline auto getFont() { return m_font; }
			inline auto getSize() { return m_size; }
			inline auto getColor() { return m_color; }

			void addString(const String & string);

			inline Text build() { return std::move(m_text); }

		private:
			const asset::AssetRegistry & m_assets;

			render::allegro::Text m_text;

			std::string m_font = "default";
			unsigned int m_size = 12u;
			ALLEGRO_COLOR m_color = { 0.0f, 0.0f, 0.0f, 1.0f };
		};
	}
}