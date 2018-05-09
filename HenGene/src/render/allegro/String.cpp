
#include "String.h"

#include <allegro5/allegro_font.h>

namespace
{
	static bool isWhitespace(int codepoint)
	{
		switch (codepoint)
		{
		case ' ':
			return true;
		default:
			return false;
		}
	}
	static bool isLinebreaker(int codepoint)
	{
		switch (codepoint)
		{
		case ',':
		case '.':
		case ':':
		case ';':
		case '-':
		case '!':
		case '?':
			return true;
		default:
			return false;
		}
	}

	static void renderString(
		const ALLEGRO_FONT * font, const ALLEGRO_USTR * str, const ALLEGRO_COLOR & color,
		glm::ivec2 position, int begin, int end
	) {
		for (int i = begin; i < end;)
		{
			const auto codepoint = al_ustr_get_next(str, &i);
			al_draw_glyph(font, color, position.x, position.y, codepoint);
			position.x += al_get_glyph_advance(font, codepoint, al_ustr_get(str, i));
		}
	}
	
	static glm::ivec2 renderString(
		const ALLEGRO_FONT * font, const ALLEGRO_USTR * str, const ALLEGRO_COLOR & color,
		const glm::ivec2 & offset, const glm::ivec2 & position, const glm::ivec2 & size
	) {
		auto currentPos = position;

		for (int index = 0, codepoint = 0; codepoint >= 0;)
		{
			const auto pos = currentPos;
			const int begin = index;

			int end = index;
			while (true)
			{
				const auto previous = index;
				codepoint = al_ustr_get_next(str, &index);

				// At the end of a string, mark end and terminate immediately
				if (codepoint < 0)
				{
					end = index;
					break;
				}
				// Mark the current location of the whitespace and move to the next non-whitespace character
				if (isWhitespace(codepoint))
					end = index++ - 1;

				// Advance position and check bounds, if outside width terminate
				currentPos.x += al_get_glyph_advance(font, codepoint, al_ustr_get(str, index));
				if (currentPos.x >= size.x)
				{
					currentPos.x = 0;
					currentPos.y += al_get_font_line_height(font) + 1;

					// If no previous breakpoints have been found, split at current character, otherwise split at breakpoint
					if (begin == end)
						end = index = previous;
					else
						index = end;
					break;
				}
				if (isLinebreaker(codepoint))
					end = index;
			}
			renderString(font, str, color, pos + offset, begin, end);
		}
		return currentPos;
	}
}

render::allegro::String::String(const std::string & str)
	: m_handle(al_ustr_new(str.c_str()))
{}
render::allegro::String::String(String && other)
{
	*this = std::move(other);
}
render::allegro::String::~String()
{
	if (m_handle != nullptr)
		al_ustr_free(m_handle);
}

render::allegro::String & render::allegro::String::operator=(String && other)
{
	if (this != &other)
	{
		std::swap(m_handle, other.m_handle);
		m_font = other.m_font;
		m_size = other.m_size;
		m_flags = other.m_flags;
		m_color = other.m_color;
	}
	return *this;
}

std::string render::allegro::String::getString() const
{
	return al_cstr(m_handle);
}
glm::vec4 render::allegro::String::getDimensions() const
{
	if (!m_font && !m_font->get(m_size, m_flags))
		return {};
	glm::ivec4 dims;
	al_get_ustr_dimensions(m_font->get(m_size, m_flags), m_handle, &dims.x, &dims.y, &dims.z, &dims.w);
	return { dims };
}

glm::vec2 render::allegro::String::draw(const glm::vec2 & pos) const
{
	return draw(pos, glm::vec4{ pos, 1000000.0f, 1000000.0f });
}
glm::vec2 render::allegro::String::draw(const glm::vec2 & pos, const glm::vec4 & bbox) const
{
	if (!m_font || !m_font->get(m_size, m_flags))
		return {};
	return renderString(
		m_font->get(m_size, m_flags), m_handle, m_color,
		{ bbox.x, bbox.y }, { pos.x - bbox.x, pos.y - bbox.y }, { bbox.z, bbox.w }
	);
}
