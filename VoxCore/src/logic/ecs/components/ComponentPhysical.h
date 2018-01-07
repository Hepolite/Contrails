
#pragma once

#include "util/Physics.h"
#include "world/World.h"

namespace logic
{
	namespace ecs
	{
		struct ComponentLocation
		{
			world::World * m_world = nullptr;
			LengthVec m_pos;
		};
		struct ComponentVelocity
		{
			SpeedVec m_vel;
		};
		struct ComponentAcceleration
		{
			AccelerationVec m_acc;
		};
	}
}