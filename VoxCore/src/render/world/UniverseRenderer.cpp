
#include "UniverseRenderer.h"

#include "render/world/WorldRenderer.h"
#include "logic/event/EventListener.h"
#include "logic/event/WorldEvents.h"

#include <unordered_map>

class render::world::UniverseRenderer::Impl
{
public:
	::world::Universe * m_universe = nullptr;

	logic::event::EventBus * m_bus = nullptr;
	logic::event::Listener m_worldCreate;
	logic::event::Listener m_worldDestroy;

	void createWorld(const std::string & name);
	void destroyWorld(const std::string & name);

private:
	std::unordered_map<std::string, WorldRenderer> m_worlds;
};

void render::world::UniverseRenderer::Impl::createWorld(const std::string & name)
{
	m_worlds.emplace(name, WorldRenderer{});
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

void render::world::UniverseRenderer::inject(logic::event::EventBus & bus)
{
	m_impl->m_bus = &bus;
	m_impl->m_worldCreate = bus.add<logic::event::WorldCreate>([this](auto & event) {});
	m_impl->m_worldDestroy = bus.add<logic::event::WorldDestroy>([this](auto & event) {});
}
void render::world::UniverseRenderer::inject(::world::Universe & universe)
{
	m_impl->m_universe = &universe;
}
