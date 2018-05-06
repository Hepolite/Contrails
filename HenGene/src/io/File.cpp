
#include "File.h"

#include <filesystem>
#include <fstream>
#include <plog/Log.h>
#include <sstream>

bool io::File::exists() const
{
	return std::experimental::filesystem::is_regular_file(m_path);
}
bool io::File::create() const
{
	if (exists())
		return false;
	std::ofstream stream{ m_path };
	stream.close();
	return exists();
}
bool io::File::erase() const
{
	return std::remove(m_path.c_str()) == 0;
}

std::string io::File::read() const
{
	std::ifstream file{ m_path };
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}
std::string io::File::parse() const
{
	std::ifstream stream{ m_path };
	if (!stream.is_open())
	{
		LOG_WARNING << "Could not open file " << m_path;
		return "";
	}

	bool firstLine = true;

	std::stringstream buffer;
	for (std::string line; std::getline(stream, line); )
	{
		if (!firstLine)
			buffer << '\n';
		firstLine = false;

		if (line.find("#include ") != std::string::npos)
		{
			auto first = line.find_first_of('\"');
			auto last = line.find_last_of('\"');
			if (first != std::string::npos && last != std::string::npos)
			{
				File child{ line.substr(first + 1, last - first - 1) };
				buffer << child.parse();
			}
		}
		else
			buffer << line;
	}
	return buffer.str();
}
bool io::File::write(const std::string & data) const
{
	std::ofstream stream{ m_path };
	if (!stream.is_open())
	{
		LOG_WARNING << "Could not open file " << m_path;
		return false;
	}
	stream << data;
	return true;
}
bool io::File::writeDangerous(const unsigned char * data, unsigned int size) const
{
	LOG_WARNING << "Attempting to write dangerously to " << m_path << "! This should not be normally done!";

	std::fstream stream{ m_path, std::ios::out | std::ios::binary };
	if (!stream.is_open())
	{
		LOG_WARNING << "Could not open file " << m_path;
		return false;
	}
	stream.write(reinterpret_cast<const char*>(data), size);
	return false;
}

std::string io::File::getFolder() const
{
	const auto end = m_path.find_last_of('/');
	return end == std::string::npos ? "" : m_path.substr(0, end);
}
std::string io::File::getName() const
{
	const auto start = m_path.find_last_of('/');
	const auto end = m_path.find_last_of('.');

	if (end == std::string::npos)
		return m_path;
	return start == std::string::npos ? m_path.substr(0, end - start - 1) : m_path.substr(start + 1, end - start - 1);
}
std::string io::File::getExtension() const
{
	const auto start = m_path.find_last_of('.');
	return start == std::string::npos ? "" : m_path.substr(start + 1);
}
