
#include "UniverseSaver.h"

#include "logic/event/ChunkEvents.h"
#include "world/detail/Limits.h"

void world::io::UniverseSaver::inject(logic::event::EventBus & bus)
{
	m_chunkChange = bus.add<logic::event::ChunkChange>([this](auto & event)
	{
		const auto it = m_savers.find(event.m_world->getName());
		if (it != m_savers.end())
			it->second->schedule(event.m_cpos >> data::REGION_SIZE_LG<int>);
	});
}

bool world::io::UniverseSaver::open(const World & world)
{
	if (m_savers.find(world.getName()) != m_savers.end())
		return false;
	::io::Folder folder{ m_root.getPath() + "/" + world.getName() };
	auto [it, inserted] = m_savers.emplace(world.getName(), std::make_unique<WorldSaver>(folder));
	if (inserted)
		it->second->inject(world);
	return true;
}
bool world::io::UniverseSaver::close(const World & world)
{
	if (m_savers.find(world.getName()) == m_savers.end())
		return false;
	m_savers.erase(world.getName());
	return true;
}
