
#include "StringGeneric.h"

#include <sstream>
#include <iterator>

std::vector<std::string> string::split(const std::string & string, const char delim)
{
	std::vector<std::string> elements;
	std::stringstream stream{ string };
	std::string item;
	auto out = std::back_inserter(elements);
	while (std::getline(stream, item, delim))
		*(out++) = item;
	return elements;
}
