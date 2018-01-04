
#include "Universe.h"

#include "logic/event/WorldEvents.h"

#include <plog/Log.h>

void world::Universe::createWorld(const std::string & name)
{
	if (m_worlds.find(name) != m_worlds.end())
	{
		LOG_WARNING << "A world with the name " << name << " already exists";
		return;
	}

	m_worlds.emplace(name, std::make_unique<World>());
	
	if (m_bus != nullptr)
		m_bus->post(logic::event::WorldCreate{ name });
}
void world::Universe::destroyWorld(const std::string & name)
{
	if (m_worlds.find(name) == m_worlds.end())
	{
		LOG_WARNING << "A world with the name " << name << " does not exists";
		return;
	}

	m_worlds.erase(name);

	if (m_bus != nullptr)
		m_bus->post(logic::event::WorldDestroy{ name });
}

bool world::Universe::hasWorld(const std::string & name) const
{
	return m_worlds.find(name) != m_worlds.end();
}

world::World * world::Universe::getWorld(const std::string & name) const
{
	const auto it = m_worlds.find(name);
	return it == m_worlds.end() ? nullptr : it->second.get();
}
