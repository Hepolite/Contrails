
#include "SystemPhysical.h"

void logic::ecs::SystemMovement::process(const Time & t, const Time & dt) const
{
	auto & locations = getData<ComponentLocation>();
	auto & velocities = getData<ComponentVelocity>();

	for (const auto & entity : *this)
		locations[entity].m_pos += velocities[entity].m_vel * dt;
}

void logic::ecs::SystemAccelerate::process(const Time & t, const Time & dt) const
{
	auto & velocities = getData<ComponentVelocity>();
	auto & accelerations = getData<ComponentAcceleration>();

	for (const auto & entity : *this)
		velocities[entity].m_vel += accelerations[entity].m_acc * dt;
}
