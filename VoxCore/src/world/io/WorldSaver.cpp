
#include "WorldSaver.h"

#include "world/World.h"

#include <plog/Log.h>

world::io::WorldSaver::WorldSaver(const ::io::Folder & root) : m_root(root) {}

void world::io::WorldSaver::inject(const World & world)
{
	m_world = &world;
}
void world::io::WorldSaver::inject(logic::event::EventBus & bus)
{
	setupListeners(bus);
}

void world::io::WorldSaver::setupListeners(logic::event::EventBus & bus)
{
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
