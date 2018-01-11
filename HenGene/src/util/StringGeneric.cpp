
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

std::string string::replace(std::string string, const std::string & sub, const std::string & rep)
{
	if (string.length() < sub.length() || sub.empty())
		return string;
	const std::size_t pos = string.find(sub);
	if (pos == std::string::npos)
		return string;
	const std::size_t subSize = sub.length();
	string.replace(pos, subSize, rep);
	return string;
}
std::string string::replaceAll(std::string string, const std::string & sub, const std::string & rep)
{
	if (string.length() < sub.length() || sub.empty())
		return string;

	const std::size_t subSize = sub.length();
	const std::size_t repSize = rep.length();

	for (std::size_t pos = 0; ; pos += repSize)
	{
		pos = string.find(sub, pos);
		if (pos == std::string::npos)
			break;
		if (subSize == repSize)
			string.replace(pos, subSize, rep);
		else
		{
			string.erase(pos, subSize);
			string.insert(pos, rep);
		}
	}
	return string;
}
