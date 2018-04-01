
#include "UniverseRenderer.h"

#include "logic/event/WorldEvents.h"

#include <plog/Log.h>

namespace
{
	constexpr const char * DATA_PATH = "data/universe/blocks/";
}

void world::render::UniverseRenderer::inject(const Universe & universe)
{
	m_universe = &universe;
}
void world::render::UniverseRenderer::inject(asset::AssetRegistry & assets)
{
	m_assets = &assets;
}
void world::render::UniverseRenderer::inject(logic::event::EventBus & bus)
{
	m_bus = &bus;
	m_worldCreate = bus.add<logic::event::WorldCreate>([this](auto & event) { createWorld(event.m_name); });
	m_worldDestroy = bus.add<logic::event::WorldDestroy>([this](auto & event) { destroyWorld(event.m_name); });
}
void world::render::UniverseRenderer::inject(::render::uboRegistry & ubos)
{
	m_ubos = &ubos;
}

void world::render::UniverseRenderer::createWorld(const std::string & name)
{
	if (m_universe == nullptr || !m_universe->hasWorld(name))
	{
		LOG_WARNING << "Attempted to create world renderer without universe or world " << name;
		return;
	}

	auto world = std::make_unique<WorldRenderer>();
	if (m_assets != nullptr)
		world->inject(*m_assets);
	if (m_bus != nullptr)
		world->inject(*m_bus);
	if (m_ubos != nullptr)
		world->inject(*m_ubos);
	world->inject(*m_universe->getWorld(name));
	world->load(DATA_PATH);
	m_worlds[name] = std::move(world);
}
void world::render::UniverseRenderer::destroyWorld(const std::string & name)
{
	m_worlds.erase(name);
}
bool world::render::UniverseRenderer::hasWorld(const std::string & name) const
{
	return m_worlds.find(name) != m_worlds.end();
}
world::render::WorldRenderer * world::render::UniverseRenderer::getWorld(const std::string & name)
{
	auto & it = m_worlds.find(name);
	return it == m_worlds.end() ? nullptr : it->second.get();
}
