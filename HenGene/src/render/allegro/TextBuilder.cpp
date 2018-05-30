
#include "TextBuilder.h"

void render::allegro::TextBuilder::addString(const std::string & string)
{
	auto & component = m_text.add<ComponentString>();
	component.setFont(m_assets.get<Font>(m_font));
	component.setString(string);
	component.setSize(m_size);
	component.setColor(m_color);
}
