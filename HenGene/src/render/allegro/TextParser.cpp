
#include "TextParser.h"

void render::allegro::TextParser::parse(const std::string & string)
{


	m_builder.addString(string);
}

render::allegro::Text render::allegro::TextParser::build()
{
	return m_builder.build();
}