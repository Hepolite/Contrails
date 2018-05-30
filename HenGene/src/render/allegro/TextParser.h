
#pragma once

#include "render/allegro/String.h"
#include "render/allegro/TextBuilder.h"

namespace render
{
	namespace allegro
	{
		class TextParser
		{
		public:
			TextParser() = delete;
			TextParser(const asset::AssetRegistry & assets) : m_builder(assets) {}
			TextParser(const TextParser &) = delete;
			TextParser(TextParser &&) = delete;
			~TextParser() = default;

			TextParser & operator=(const TextParser &) = delete;
			TextParser & operator=(TextParser &&) = delete;

			inline auto empty() const { return m_builder.empty(); }
			inline auto size() const { return m_builder.size(); }

			inline auto getFont() { return m_builder.getFont(); }
			inline auto getSize() { return m_builder.getSize(); }
			inline auto getColor() { return m_builder.getColor(); }

			void parse(const std::string & string);

			Text build();

		private:
			TextBuilder m_builder;
		};
	}
}