
#include "Universe.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "logic/event/WorldEvents.h"
#include "world/World.h"

#include <plog/Log.h>

namespace
{
	const io::Folder WORLD_PATH{ "data/universe/worlds" };
	constexpr const char * DATA_PATH = "data/universe/blocks/";
}

world::Universe::Universe() : m_saver(WORLD_PATH) {}
world::Universe::~Universe() = default;

void world::Universe::inject(core::scene::Scene & scene)
{
	m_scene = &scene;
}
void world::Universe::inject(logic::event::EventBus & bus)
{
	m_bus = &bus;
	m_saver.inject(bus);
}

void world::Universe::createWorld(const std::string & name, bool autosave)
{
	if (hasWorld(name))
	{
		LOG_WARNING << "A world with the name " << name << " already exists";
		return;
	}
	LOG_INFO << "Creating world " << name << "...";

	auto world = m_worlds.emplace(name, std::make_unique<World>(name)).first->second.get();
	world->load(DATA_PATH);
	if (m_scene != nullptr)
	{
		// TODO: Destroy the entity at some point
		const auto entity = m_scene->createEntity<ComponentWorld>();
		m_scene->getEntityData<ComponentWorld>(entity).m_name = name;
	}
	if (m_bus != nullptr)
	{
		world->inject(*m_bus);
		m_bus->post(logic::event::WorldCreate{ name });
	}

	if (autosave)
		m_saver.open(*world);
}
void world::Universe::destroyWorld(const std::string & name)
{
	if (!hasWorld(name))
	{
		LOG_WARNING << "A world with the name " << name << " does not exists";
		return;
	}
	LOG_INFO << "Destroying world " << name << "...";

	if (m_bus != nullptr)
		m_bus->post(logic::event::WorldDestroy{ name });
	m_saver.close(*m_worlds[name]);
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
