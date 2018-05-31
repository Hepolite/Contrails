
#include "TextParser.h"

#include "util/StringParsing.h"

void render::allegro::TextParser::parse(const String & string)
{
	for (unsigned int current = 0u; current < string.length();)
	{
		const auto begin = string.find('{', current);
		const auto end = string.find('}', begin);

		if (current != begin)
		{
			m_builder.addString(string.substr(current, begin));
			current = begin;
		}
		else
		{
			const auto data = string.substr(begin + 1u, end).getString();
			const auto parts = string::parseVector<std::string>(data, "", ' ');

			if (parts.size() == 2u && parts[0u] == "size")
				m_builder.setSize(string::parse<unsigned int>(parts[1], getSize()));
			else if (parts.size() == 2u && parts[0u] == "font")
				m_builder.setFont(parts[1]);
			else if (parts.size() == 5u && parts[0u] == "color")
				m_builder.setColor({
					string::parse<float>(parts[1]),
					string::parse<float>(parts[2]),
					string::parse<float>(parts[3]),
					string::parse<float>(parts[4])
				});

			if (end == String::END)
				break;
			current = end + 1u;
		}
	}
}

render::allegro::Text render::allegro::TextParser::build()
{
	return m_builder.build();
}