
#include "WorldLoader.h"

#include "world/BlockRegistry.h"
#include "world/World.h"
#include "util/StringParsing.h"

#include <plog/Log.h>
#include <string>

namespace
{
	constexpr const char * ATTR_BLOCK_ID = "id";

	const std::string EXTENSION_REGION_FILE = "rvd";
	constexpr auto INVALID_REGION_FILE_POS = glm::ivec3{ std::numeric_limits<int>::max() };
}

world::io::WorldLoader::WorldLoader(const::io::Folder & root)
	: m_loader(root), m_root(root)
{}
world::io::WorldLoader::~WorldLoader()
{
	m_working = false;
	if (m_worker.joinable())
		m_worker.join();
}

void world::io::WorldLoader::readWorld()
{
	for (const auto & file : m_root.getFiles())
	{
		if (file.getExtension() != EXTENSION_REGION_FILE)
			continue;

		const auto rpos = string::parseVec3<int>(file.getName(), INVALID_REGION_FILE_POS, '_');
		if (rpos != INVALID_REGION_FILE_POS)
			m_tasks.push_back(rpos);
	}

	m_worker = std::thread{ [this]() { work(); } };
}
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

// ...

bool world::io::WorldLoader::extract(glm::ivec3 & rpos)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	if (m_tasks.empty())
		return false;
	rpos = m_tasks.back();
	m_tasks.pop_back();
	return true;
}

void world::io::WorldLoader::work()
{
	glm::ivec3 rpos;
	while (extract(rpos))
	{
		if (!m_working)
			break;
		m_loader.read(*m_world, rpos);
	}
}
void world::io::WorldLoader::finish()
{
	while (!m_tasks.empty())
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}
