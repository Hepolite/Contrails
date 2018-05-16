
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
#include <vector>

namespace render
{
	namespace allegro
	{
		struct Segment
		{
			std::function<void(const glm::ivec3 & offset, const Time & t)> m_draw = nullptr;

			unsigned int m_startIndex = 0u;
			unsigned int m_endIndex = 0u;
			glm::ivec2 m_pos = {};
			glm::ivec2 m_size = {};
		};
		struct Line
		{
			std::vector<Segment> m_segments;

			glm::ivec2 m_pos = {};
			glm::ivec2 m_size = {};
		};

		// ...

		class ComponentBase
		{
		public:
			virtual bool calculateSegment(Segment & segment, const glm::ivec4 & bbox) const = 0;
		};

		class ComponentString : public ComponentBase
		{
		public:
			void setString(const String & str);
			void setFont(const asset::Ref<Font> & font);
			void setSize(unsigned int size);
			void setFlags(unsigned int flags);
			void setColor(const ALLEGRO_COLOR & color);

			unsigned int getLength() const;
			unsigned int getCodepoint(int & index) const;

			virtual bool calculateSegment(Segment & segment, const glm::ivec4 & bbox) const override final;

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

			virtual bool calculateSegment(Segment & segment, const glm::ivec4 & bbox) const override final;

		private:
			asset::Ref<Sprite> m_sprite;

			ALLEGRO_COLOR m_color{ 0.0f, 0.0f, 0.0f, 1.0f };
		};

		// ...

		class Text
		{
		public:
			template<typename T, typename ...Args> T & add(const Args & ...);

			void draw(const glm::vec2 & pos, const Time & t) const;
			void draw(const glm::vec2 & pos, const glm::vec2 & size, const Time & t) const;

		private:
			std::vector<std::unique_ptr<ComponentBase>> m_components;
		};
	}
}