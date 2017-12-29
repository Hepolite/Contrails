
#pragma once

#include <string>

namespace io
{
	class File
	{
	public:
		File() = delete;
		File(const char* path) : m_path(path) {}
		File(const std::string& path) : m_path(path) {}

		bool exists() const;
		bool create() const;
		bool erase() const;

		std::string read() const;
		std::string parse() const;
		bool write(const std::string & data) const;

		std::string getPath() const { return m_path; }
		std::string getFolder() const;
		std::string getName() const;
		std::string getExtension() const;

	private:
		std::string m_path;
	};
}