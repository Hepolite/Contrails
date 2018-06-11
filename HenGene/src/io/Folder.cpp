
#include "Folder.h"

#include "util/StringGeneric.h"

#include <filesystem>

bool io::Folder::exists() const
{
	return std::experimental::filesystem::is_directory(m_path);
}
bool io::Folder::create() const
{
	return std::experimental::filesystem::create_directories(m_path);
}
bool io::Folder::erase(bool recursive) const
{
	if (recursive)
	{
		for (const auto & folder : getFolders())
			folder.erase(true);
		for (const auto & file : getFiles())
			file.erase();
	}
	return std::experimental::filesystem::remove(m_path);
}

std::vector<io::File> io::Folder::getFiles() const
{
	std::vector<File> files;
	for (auto & item : std::experimental::filesystem::directory_iterator(m_path))
	{
		if (std::experimental::filesystem::is_regular_file(item))
			files.emplace_back(string::replaceAll(item.path().string(), "\\", "/"));
	}
	return files;
}
std::vector<io::Folder> io::Folder::getFolders() const
{
	std::vector<Folder> folders;
	for (auto & item : std::experimental::filesystem::directory_iterator(m_path))
	{
		if (std::experimental::filesystem::is_directory(item))
			folders.emplace_back(string::replaceAll(item.path().string(), "\\", "/"));
	}
	return folders;
}

std::string io::Folder::getFolder() const
{
	const auto end = m_path.find_last_of('/');
	return end == std::string::npos ? "" : m_path.substr(0, end);
}
std::string io::Folder::getName() const
{
	const auto start = m_path.find_last_of('/');
	return start == std::string::npos ? m_path : m_path.substr(start + 1);
}