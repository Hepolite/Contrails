
#pragma once

#include "util/StringGeneric.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

namespace string
{
	template<typename T>
	T parse(const std::string & string, const T & def = T{})
	{
		static_assert(false, "No overloaded function exists");
	}
	template<typename T>
	std::vector<T> parseVector(const std::string & string, const T & def = T{}, const char delim = ' ')
	{
		std::vector<T> data;
		for (const auto & value : split(string, delim))
			data.push_back(parse<T>(value, def));
		return data;
	}

	// ...

	template<> inline bool parse(const std::string & string, const bool & def)
	{
		if (string.empty())
			return def;
		switch (string[0u])
		{
		case '1': case 't': case 'T': case 'y': case 'Y':
			return true;
		case '0': case 'f': case 'F': case 'n': case 'N':
			return false;
		default:
			return def;
		}
	}
	template<> inline float parse(const std::string & string, const float & def)
	{
		try { return std::stof(string); }
		catch (...) { return def; }
	}
	template<> inline int parse(const std::string & string, const int & def)
	{
		try { return std::stoi(string); }
		catch (...) { return def; }
	}
	template<> inline unsigned int parse(const std::string & string, const unsigned int & def)
	{
		try { return std::stoul(string); }
		catch (...) { return def; }
	}
	template<> inline std::string parse(const std::string & string, const std::string & def)
	{
		return string;
	}

	// ...

	template<> inline std::vector<std::string> parseVector(const std::string & string, const std::string & def, const char delim)
	{
		return split(string, delim);
	}

	// ...

	template<typename T> glm::tvec2<T> parseVec2(const std::string & string, const glm::tvec2<T> & def = {}, const char delim = ' ')
	{
		const auto data = parseVector<T>(string, T{}, delim);
		switch (data.size())
		{
		case 1u:
			return glm::tvec2<T>{ data[0u] };
		case 2u:
			return glm::tvec2<T>{ data[0u], data[1u] };
		default:
			return def;
		}
	}
	template<typename T> glm::tvec3<T> parseVec3(const std::string & string, const glm::tvec3<T> & def = {}, const char delim = ' ')
	{
		const auto data = parseVector<T>(string, T{}, delim);
		switch (data.size())
		{
		case 1u:
			return glm::tvec3<T>{ data[0u] };
		case 3u:
			return glm::tvec3<T>{ data[0u], data[1u], data[2u] };
		default:
			return def;
		}
	}
	template<typename T> glm::tvec4<T> parseVec4(const std::string & string, const glm::tvec4<T> & def = {}, const char delim = ' ')
	{
		const auto data = parseVector<T>(string, T{}, delim);
		switch (data.size())
		{
		case 1u:
			return glm::tvec4<T>{ data[0u] };
		case 4u:
			return glm::tvec4<T>{ data[0u], data[1u], data[2u], data[3u] };
		default:
			return def;
		}
	}

	template<> inline glm::vec2 parse(const std::string & string, const glm::vec2 & def)
	{
		return parseVec2<float>(string, def, ' ');
	}
	template<> inline glm::bvec2 parse(const std::string & string, const glm::bvec2 & def)
	{
		return parseVec2<bool>(string, def, ' ');
	}
	template<> inline glm::ivec2 parse(const std::string & string, const glm::ivec2 & def)
	{
		return parseVec2<int>(string, def, ' ');
	}
	template<> inline glm::uvec2 parse(const std::string & string, const glm::uvec2 & def)
	{
		return parseVec2<unsigned int>(string, def, ' ');
	}
	template<> inline glm::vec3 parse(const std::string & string, const glm::vec3 & def)
	{
		return parseVec3<float>(string, def, ' ');
	}
	template<> inline glm::bvec3 parse(const std::string & string, const glm::bvec3 & def)
	{
		return parseVec3<bool>(string, def, ' ');
	}
	template<> inline glm::ivec3 parse(const std::string & string, const glm::ivec3 & def)
	{
		return parseVec3<int>(string, def, ' ');
	}
	template<> inline glm::uvec3 parse(const std::string & string, const glm::uvec3 & def)
	{
		return parseVec3<unsigned int>(string, def, ' ');
	}
	template<> inline glm::vec4 parse(const std::string & string, const glm::vec4 & def)
	{
		return parseVec4<float>(string, def, ' ');
	}
	template<> inline glm::bvec4 parse(const std::string & string, const glm::bvec4 & def)
	{
		return parseVec4<bool>(string, def, ' ');
	}
	template<> inline glm::ivec4 parse(const std::string & string, const glm::ivec4 & def)
	{
		return parseVec4<int>(string, def, ' ');
	}
	template<> inline glm::uvec4 parse(const std::string & string, const glm::uvec4 & def)
	{
		return parseVec4<unsigned int>(string, def, ' ');
	}
}