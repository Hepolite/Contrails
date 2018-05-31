
#pragma once

#include "util/Physics.h"
#include "world/World.h"

namespace logic
{
	namespace ecs
	{
		struct ComponentPosition
		{
			world::World * m_world = nullptr;
			LengthVec m_pos{};
			LengthVec m_prevPos = m_pos;
		};

		struct ComponentVelocity
		{
			SpeedVec m_vel{};
		};
		struct ComponentAcceleration
		{
			AccelerationVec m_acc{};
		};
		struct ComponentGravity
		{
			AccelerationVec m_grv{ 0.0_ms2, -9.8_ms2, 0.0_ms2 };
		};
	}
}