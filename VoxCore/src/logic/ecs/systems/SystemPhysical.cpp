
#include "SystemPhysical.h"

void logic::ecs::SystemMovement::process(const Time & t, const Time & dt) const
{
	auto & position = getData<ComponentPosition>();
	auto & velocity = getData<ComponentVelocity>();

	for (const auto & entity : *this)
		position[entity].m_pos += velocity[entity].m_vel * dt;
}

void logic::ecs::SystemAcceleration::process(const Time & t, const Time & dt) const
{
	auto & velocity = getData<ComponentVelocity>();
	auto & acceleration = getData<ComponentAcceleration>();

	for (const auto & entity : *this)
	{
		velocity[entity].m_vel += acceleration[entity].m_acc * dt;
		acceleration[entity].m_acc = AccelerationVec{};
	}
}

void logic::ecs::SystemGravitation::process(const Time & t, const Time & dt) const
{
	auto & acceleration = getData<ComponentAcceleration>();
	auto & gravity = getData<ComponentGravity>();

	for (const auto & entity : *this)
		acceleration[entity].m_acc += gravity[entity].m_grv;
}
