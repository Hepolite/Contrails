
#include "UniverseRenderer.h"

#include "render/world/WorldRenderer.h"
#include "logic/event/EventListener.h"
#include "logic/event/WorldEvents.h"

#include <plog/Log.h>
#include <unordered_map>

namespace
{
	constexpr const char * DATA_PATH = "data/universe/blocks/";
}

class render::world::UniverseRenderer::Impl
{
public:
	void createWorld(const std::string & name);
	void destroyWorld(const std::string & name);

	::world::Universe * m_universe = nullptr;

	logic::event::EventBus * m_bus = nullptr;
	logic::event::Listener m_worldCreate;
	logic::event::Listener m_worldDestroy;

private:
	std::unordered_map<std::string, WorldRenderer> m_worlds;
};

void render::world::UniverseRenderer::Impl::createWorld(const std::string & name)
{
	if (m_bus == nullptr || m_universe == nullptr)
	{
		LOG_WARNING << "Attempted to create world renderer before bus and/or universe has been injected";
		return;
	}
	if (!m_universe->hasWorld(name))
	{
		LOG_WARNING << "Attempted to create world renderer for a world '" << name << "' which does not exist";
		return;
	}

	m_worlds.emplace(name, WorldRenderer{});

	auto & renderer = m_worlds[name];
	renderer.inject(*m_universe->getWorld(name));
	renderer.inject(*m_bus);
	renderer.load(DATA_PATH);
}
void render::world::UniverseRenderer::Impl::destroyWorld(const std::string & name)
{
	m_worlds.erase(name);
}

// ...

render::world::UniverseRenderer::UniverseRenderer()
{
	m_impl = std::make_unique<Impl>();
}
render::world::UniverseRenderer::~UniverseRenderer()
{
	m_impl->m_bus->remove(m_impl->m_worldCreate);
	m_impl->m_bus->remove(m_impl->m_worldDestroy);
}

void render::world::UniverseRenderer::inject(::logic::event::EventBus & bus)
{
	m_impl->m_bus = &bus;
	m_impl->m_worldCreate = bus.add<logic::event::WorldCreate>([this](auto & event) { m_impl->createWorld(event.m_name); });
	m_impl->m_worldDestroy = bus.add<logic::event::WorldDestroy>([this](auto & event) { m_impl->destroyWorld(event.m_name); });
}
void render::world::UniverseRenderer::inject(::world::Universe & universe)
{
	m_impl->m_universe = &universe;
}

