
#pragma once

#include "logic/ecs/components/ComponentPhysical.h"
#include "logic/ecs/System.h"

namespace logic
{
	namespace ecs
	{
		class SIMPLE_SYSTEM(SystemMovement, ComponentPosition, ComponentVelocity);
		class SIMPLE_SYSTEM(SystemAcceleration, ComponentVelocity, ComponentAcceleration);
		class SIMPLE_SYSTEM(SystemGravitation, ComponentAcceleration, ComponentGravity);
	}
}