
#include "Folder.h"

#include <dirent/dirent.h>

namespace
{
	template<class T>
	std::vector<T> getEntry(const std::string& path, int filter)
	{
		DIR* dir = opendir(path.c_str());
		if (dir == nullptr)
			return{};
		struct stat st;

		std::vector<T> entries;
		for (struct dirent* ent; (ent = readdir(dir)) != nullptr; )
		{
			const std::string file_name = ent->d_name;
			const std::string full_file_name = path + "/" + file_name;

			if (file_name[0] == '.')
				continue;
			if (stat(full_file_name.c_str(), &st) == -1)
				continue;

			if ((st.st_mode & filter) != 0)
				entries.emplace_back(full_file_name);
		}
		return entries;
	}
}

bool io::Folder::exists() const
{
	struct stat dirInfo;
	return stat(m_path.c_str(), &dirInfo) == 0 && (dirInfo.st_mode & S_IFDIR) != 0;
}

std::vector<io::File> io::Folder::getFiles() const
{
	return getEntry<File>(m_path, S_IFMT & ~S_IFDIR);
}
std::vector<io::Folder> io::Folder::getFolders() const
{
	return getEntry<Folder>(m_path, S_IFDIR);
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