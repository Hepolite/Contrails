
#include "Text.h"

#include "util/MathGeneric.h"

#include <allegro5/allegro_font.h>

namespace
{
	bool canBreakLines(unsigned int codepoint)
	{
		switch (codepoint)
		{
		case '\0':
		case '\n':
		case ' ':
		case '.':
		case ',':
		case '-':
		case ':':
		case ';':
		case '!':
		case '?':
			return true;
		default:
			return false;
		}
	}
}

std::optional<render::allegro::Segment> render::allegro::ComponentString::calculateSegment(
	unsigned int index, const int width) const
{
	if (!m_font || !m_font->get(m_size, m_flags) || m_string.at(index) == '\0')
		return std::nullopt;
	const auto font = m_font->get(m_size, m_flags);

	Segment segment;
	segment.m_startIndex = index;

	while (true)
	{
		const auto cp = m_string.next(index);
		if (canBreakLines(cp))
			segment.m_endIndex = index;
		if (cp == '\n')
			segment.m_size.x = width;
		if (cp == '\0' || cp == '\n')
			break;

		const auto advance = al_get_glyph_advance(font, cp, m_string.at(index));
		if (segment.m_size.x + advance <= width)
		{
			int height, _;
			al_get_glyph_dimensions(font, cp, &_, &_, &_, &height);

			segment.m_size.x += advance;
			segment.m_size.y = math::max(segment.m_size.y, height);
		}
		else
		{
			if (segment.m_endIndex == 0u)
				segment.m_endIndex = index;
			segment.m_size.x = math::max(1, width);
			break;
		}
	}
	return std::make_optional(segment);
}

// ...

std::optional<render::allegro::Line> render::allegro::Text::calculateLine(
	unsigned int component, unsigned int index, int width
) const
{
	if (component >= m_components.size())
		return std::nullopt;

	Line line;
	line.m_startComponent = component;
	line.m_startIndex = index;

	while (true)
	{
		const auto segment = m_components[component]->calculateSegment(index, width - line.m_size.x);
		if (!segment)
		{
			line.m_endComponent = ++component;
			line.m_endIndex = index = 0u;

			if (component == m_components.size())
				break;
			continue;
		}
		index = segment->m_endIndex;

		if (line.m_size.x + segment->m_size.x <= width)
		{
			line.m_endComponent = component;
			line.m_endIndex = index;
			line.m_segments.push_back(segment.value());

			line.m_size.x += segment->m_size.x;
			line.m_size.y = math::max(line.m_size.y, segment->m_size.y);
		}
		else
		{
			line.m_size.x = math::max(1, width);
			break;
		}
	}
	return std::make_optional(line);

	/*
	glm::ivec2 currentPos = { 0, 0 };

	while (true)
	{
		if (component >= m_components.size())
			break;
		const auto segment = m_components[component]->calculateSegment(index, currentPos, { 0, 0, width, 10000 });
		if (!segment)
		{
			component++;
			index = 0u;

			line.m_endComponent = component;
			line.m_endIndex = index;
			continue;
		}

		index = segment->m_endIndex;
		currentPos = segment->m_pos + glm::ivec2{ segment->m_size.x, 0 };

		if (segment->m_pos.x + segment->m_size.x <= width)
		{
			line.m_segments.push_back(segment.value());
			line.m_size.x += segment->m_size.x;
			line.m_size.y = math::max(line.m_size.y, segment->m_size.y);

			if (line.m_size.x == width)
			{
				line.m_endComponent = component;
				line.m_endIndex = index;
				break;
			}
		}
		else
			break;
	}
	return line.m_segments.empty() ? std::nullopt : std::make_optional(line);*/
}

void render::allegro::Text::draw(const glm::vec2 & pos, const Time & t) const
{
	draw(pos, { 1000000.0f, 1000000.0f }, t);
}
void render::allegro::Text::draw(const glm::vec2 & pos, const glm::vec2 & size, const Time & t) const
{
	auto current = glm::ivec2{ pos };
	
	auto line = std::make_optional<Line>();
	while (line = calculateLine(line->m_endComponent, line->m_endIndex, size.x))
	{
		for (const auto & segment : line->m_segments)
		{
			if (segment.m_draw)
			{
				segment.m_draw(segment, current, t);
				current.x += segment.m_size.x;
			}
		}
		current.x = pos.x;
		current.y += line->m_size.y;
	}
}
