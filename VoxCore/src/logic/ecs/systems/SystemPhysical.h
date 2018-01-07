
#pragma once

#include "logic/ecs/components/ComponentPhysical.h"
#include "logic/ecs/System.h"
#include "util/Physics.h"

namespace logic
{
	namespace ecs
	{
		class SystemMovement : public System<ComponentLocation, ComponentVelocity>
		{
		public:
			virtual void process(const Time & t, const Time & dt) const override final;
		};

		class SystemAccelerate : public System<ComponentVelocity, ComponentAcceleration>
		{
		public:
			virtual void process(const Time & t, const Time & dt) const override final;
		};
	}
}