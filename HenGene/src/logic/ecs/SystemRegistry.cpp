
#include "SystemRegistry.h"

void logic::ecs::SystemRegistry::process(const Time & t, const Time & dt) const
{
	for (const auto & system : m_systems)
		system->process(t, dt);
}