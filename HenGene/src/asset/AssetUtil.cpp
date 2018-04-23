
#include "AssetUtil.h"

#include <plog/Log.h>

void asset::util::detail::logSearchFolder(const io::Folder & folder)
{
	LOG_INFO << "Searching " << folder.getPath() << " for assets...";
}
void asset::util::detail::logFoundAsset(const io::File & file, const std::string & name)
{
	LOG_INFO << "Found " << name << " in " << file.getPath();
}
void asset::util::detail::logCreatedFactory(const std::string & name)
{
	LOG_INFO << "Created custom asset factory for " << name;
}
