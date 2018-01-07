
#include "SystemRegistry.h"

void logic::ecs::SystemRegistry::process(const Time & t, const Time & dt)
{
	for (const auto & system : m_systems)
		system->process(t, dt);
}

void logic::ecs::SystemRegistry::addEntity(const Entity & entity)
{
	for (auto & system : m_systems)
		system->add(entity);
}
void logic::ecs::SystemRegistry::removeEntity(const Entity & entity)
{
	for (auto & system : m_systems)
		system->remove(entity);
}