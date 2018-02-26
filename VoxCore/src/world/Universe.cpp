
#include "Universe.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "logic/event/WorldEvents.h"
#include "world/World.h"

#include <plog/Log.h>

world::Universe::Universe() = default;
world::Universe::~Universe() = default;

void world::Universe::createWorld(const std::string & name)
{
	if (m_worlds.find(name) != m_worlds.end())
	{
		LOG_WARNING << "A world with the name " << name << " already exists";
		return;
	}
	LOG_INFO << "Creating world " << name << "...";

	auto world = m_worlds.emplace(name, std::make_unique<World>()).first->second.get();
	if (m_scene != nullptr)
	{
		world->inject(*m_scene);
		// TODO: Destroy the entity at some point
		const auto entity = m_scene->createEntity<ComponentWorld>();
		m_scene->getEntityData<ComponentWorld>(entity).m_name = name;
	}
	if (m_bus != nullptr)
	{
		world->inject(*m_bus);
		m_bus->post(logic::event::WorldCreate{ name });
	}
}
void world::Universe::destroyWorld(const std::string & name)
{
	if (m_worlds.find(name) == m_worlds.end())
	{
		LOG_WARNING << "A world with the name " << name << " does not exists";
		return;
	}
	LOG_INFO << "Destroying world " << name << "...";

	if (m_bus != nullptr)
		m_bus->post(logic::event::WorldDestroy{ name });
	m_worlds.erase(name);
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
