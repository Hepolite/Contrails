
#include "Text.h"

#include "util/MathGeneric.h"

#include <allegro5/allegro_font.h>

namespace
{
	bool canBreakLines(unsigned int codepoint)
	{
		switch (codepoint)
		{
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
			segment.m_size.x = bbox.w - pos.x;
		if (cp == '\0' || cp == '\n')
		{
			segment.m_endIndex = index;
			break;
		}

		glm::ivec4 dimensions;
		al_get_glyph_dimensions(font, cp, &dimensions.x, &dimensions.y, &dimensions.z, &dimensions.w);
		if (segment.m_pos.x + segment.m_size.x + dimensions.z < bbox.x + bbox.z)
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
