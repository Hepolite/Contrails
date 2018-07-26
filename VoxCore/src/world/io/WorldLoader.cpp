
#include "WorldLoader.h"

#include "world/BlockRegistry.h"
#include "world/World.h"

#include <plog/Log.h>

namespace
{
	constexpr const char * ATTR_BLOCK_ID = "id";
}

world::io::WorldLoader::WorldLoader(const::io::Folder & root)
	: m_loader(root), m_root(root)
{}

void world::io::WorldLoader::readMetadata() const
{
	::io::File header{ m_root.getPath() + "/header.xml" };

	pugi::xml_document doc;
	if (doc.load_file(header.getPath().c_str()))
		readBlockIds(doc.child("blocks"));
	else
		LOG_WARNING << "Could not load world metadata file " << header.getPath();
}
void world::io::WorldLoader::readBlockIds(const pugi::xml_node & node) const
{
	BlockRegistry registry;

	for (auto & child = node.first_child(); child; child = child.next_sibling())
	{
		// Skip the air block
		if (std::string{ "air" } != child.name())
			registry.add(child.name(), child.attribute(ATTR_BLOCK_ID).as_uint());
	}

	if (m_world != nullptr)
		m_world->inject(registry);
}
