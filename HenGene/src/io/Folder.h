
#pragma once

#include "io/File.h"

#include <string>
#include <vector>

namespace io
{
	class Folder
	{
	public:
		Folder() = delete;
		Folder(const char * path) : m_path(path) {}
		Folder(const std::string & path) : m_path(path) {}

		bool exists() const;
		bool create() const;
		bool erase(bool recursive = false) const;

		std::vector<File> getFiles() const;
		std::vector<Folder> getFolders() const;

		std::string getPath() const { return m_path; }
		std::string getFolder() const;
		std::string getName() const;

	private:
		std::string m_path;
	};
}