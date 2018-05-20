
#pragma once

#include "asset/AssetRef.h"
#include "render/allegro/Font.h"
#include "render/allegro/Sprite.h"
#include "render/allegro/String.h"
#include "render/allegro/TranslationTable.h"
#include "util/Physics.h"

#include <allegro5/color.h>
#include <functional>
#include <glm/vec2.hpp>
#include <memory>
#include <optional>
#include <vector>

namespace render
{
	namespace allegro
	{
		struct Segment
		{
			std::function<void(const glm::ivec2 & offset, const Time & t)> m_draw = nullptr;

			unsigned int m_startIndex = 0u;
			unsigned int m_endIndex = 0u;
			glm::ivec2 m_pos = {};
			glm::ivec2 m_size = {};
		};
		struct Line
		{
			std::vector<Segment> m_segments;

			unsigned int m_startComponent = 0u;
			unsigned int m_endComponent = 0u;
			unsigned int m_startIndex = 0u;
			unsigned int m_endIndex = 0u;
			glm::ivec2 m_pos = {};
			glm::ivec2 m_size = {};
		};

		// ...

		class ComponentBase
		{
		public:
			virtual std::optional<Segment> calculateSegment(
				unsigned int index, const glm::ivec2 & pos, const glm::ivec4 & bbox
			) const = 0;
		};

		class ComponentString : public ComponentBase
		{
		public:
			inline void setString(const String & string) { m_string = string; }
			inline void setFont(const asset::Ref<Font> & font) { m_font = font; }
			inline void setSize(unsigned int size) { m_size = size; }
			inline void setFlags(unsigned int flags) { m_flags = flags; }
			inline void setColor(const ALLEGRO_COLOR & color) { m_color = color; }

			virtual std::optional<Segment> calculateSegment(
				unsigned int index, const glm::ivec2 & pos, const glm::ivec4 & bbox
			) const override final;

		private:
			String m_string;

			asset::Ref<Font> m_font;
			unsigned int m_size = 8u;
			unsigned int m_flags = 0u;

			ALLEGRO_COLOR m_color{ 0.0f, 0.0f, 0.0f, 1.0f };
		};
		class ComponentTranslation : public ComponentString
		{
		public:
			ComponentTranslation(const TranslationTable & table);

			void setKey(const std::string & key);

		private:
			const TranslationTable & m_table;
		};

		class ComponentSprite : public ComponentBase
		{
		public:
			void setSprite(const asset::Ref<Sprite> & ref);
			void setColor(const ALLEGRO_COLOR & color);

			virtual std::optional<Segment> calculateSegment(
				unsigned int index, const glm::ivec2 & pos, const glm::ivec4 & bbox
			) const override final;

		private:
			asset::Ref<Sprite> m_sprite;

			ALLEGRO_COLOR m_color{ 0.0f, 0.0f, 0.0f, 1.0f };
		};

		// ...

		class Text
		{
		public:
			template<typename T, typename ...Args> T & add(const Args & ...args);

			std::optional<Line> calculateLine(
				unsigned int component, unsigned int index, const glm::ivec4 & bbox
			) const;

			void draw(const glm::vec2 & pos, const Time & t) const;
			void draw(const glm::vec2 & pos, const glm::vec2 & size, const Time & t) const;

		private:
			std::vector<std::unique_ptr<ComponentBase>> m_components;
		};
	}
}

template<typename T, typename ...Args>
inline T & render::allegro::Text::add(const Args & ...args)
{
	m_components.push_back(std::make_unique<T>(args...));
	return *static_cast<T*>(m_components.back().get());
}