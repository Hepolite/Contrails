
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
	unsigned int index, const glm::ivec2 & pos, const glm::ivec4 & bbox
) const
{
	if (!m_font || !m_font->get(m_size, m_flags))
		return std::nullopt;
	const auto font = m_font->get(m_size, m_flags);

	Segment segment;
	segment.m_startIndex = index;
	segment.m_pos = pos;

	unsigned int linebreakIndex = index;
	while (true)
	{
		const auto cp = m_string.next(index);
		if (canBreakLines(cp))
			linebreakIndex = index;
		if (cp == '\n')
			segment.m_size.x = bbox.z - pos.x;
		if (cp == '\0' || cp == '\n')
		{
			segment.m_endIndex = linebreakIndex;
			break;
		}

		glm::ivec4 dimensions;
		al_get_glyph_dimensions(font, cp, &dimensions.x, &dimensions.y, &dimensions.z, &dimensions.w);
		if (segment.m_pos.x + segment.m_size.x + dimensions.z <= bbox.z)
		{
			segment.m_size.x += dimensions.z;
			segment.m_size.y = math::max(segment.m_size.y, dimensions.w);
		}
		else
		{
			segment.m_endIndex = linebreakIndex;
			break;
		}
	}
	return segment.m_startIndex == index ? std::nullopt : std::make_optional(segment);
}

// ...

std::optional<render::allegro::Line> render::allegro::Text::calculateLine(
	unsigned int component, unsigned int index, const glm::ivec4 & bbox
) const
{
	Line line;
	line.m_startComponent = component;
	line.m_startIndex = index;

	glm::ivec2 currentPos = {};

	while (true)
	{
		if (component >= m_components.size())
			break;
		const auto segment = m_components[component]->calculateSegment(index, currentPos, bbox);
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

		if (segment->m_pos.x + segment->m_size.x <= bbox.z)
		{
			line.m_segments.push_back(segment.value());
			line.m_size.x += segment->m_size.x;
			line.m_size.y = math::max(line.m_size.y, segment->m_size.y);

			if (line.m_size.x == bbox.z)
			{
				line.m_endComponent = component;
				line.m_endIndex = index;
				break;
			}
		}
		else
			break;
	}
	return line.m_segments.empty() ? std::nullopt : std::make_optional(line);
}

void render::allegro::Text::draw(const glm::vec2 & pos, const Time & t) const
{
	draw(pos, { 1000000.0f, 1000000.0f }, t);
}
void render::allegro::Text::draw(const glm::vec2 & pos, const glm::vec2 & size, const Time & t) const
{
	auto line = std::make_optional<Line>();
	while (line = calculateLine(line->m_endComponent, line->m_endIndex, { pos, size }))
	{
		for (const auto & segment : line->m_segments)
		{
			if (segment.m_draw)
				segment.m_draw(glm::ivec2{ pos } + line->m_pos + segment.m_pos, t);
		}
	}
}
