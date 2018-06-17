
#include "WorldSaver.h"

#include "world/World.h"

#include <plog/Log.h>

world::io::WorldSaver::WorldSaver(const ::io::Folder & root)
	: m_root(root), m_saver(root)
{
	m_worker = std::thread{ [this]() { work(); } };
}
world::io::WorldSaver::~WorldSaver()
{
	m_working = false;
	m_worker.join();
	writeMetadata();
}

void world::io::WorldSaver::inject(const World & world)
{
	m_world = &world;
}

void world::io::WorldSaver::schedule(const glm::ivec3 & rpos)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	m_tasks.insert(rpos);
}
bool world::io::WorldSaver::extract(glm::ivec3 & rpos)
{
	std::lock_guard<std::mutex> guard{ m_mutex };
	if (m_tasks.empty())
		return false;
	rpos = *m_tasks.begin();
	m_tasks.erase(rpos);
	return true;
}

void world::io::WorldSaver::writeMetadata() const
{
	if (!m_root.exists())
		m_root.create();
	::io::File header{ m_root.getPath() + "/header.xml" };
	
	pugi::xml_document doc;
	writeBlockIds(doc.append_child("blocks"));

	doc.save_file(header.getPath().c_str());
}
void world::io::WorldSaver::writeBlockIds(pugi::xml_node & node) const
{
	if (m_world == nullptr)
	{
		LOG_WARNING << "Attempted to store world block ids before world is injected";
		return;
	}

	const auto & registry = m_world->getBlockRegistry();
	for (auto i = 0u; i < registry.size(); ++i)
	{
		const auto & block = registry[i];
		node.append_child(block.m_name.c_str()).append_attribute("id").set_value(block.m_id);
	}
}

// ...

void world::io::WorldSaver::work()
{
	glm::ivec3 rpos;
	while (m_working || !m_tasks.empty())
	{
		while (extract(rpos))
			m_saver.write(*m_world, rpos);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}
void world::io::WorldSaver::finish()
{
	while (!m_tasks.empty())
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
}