
#pragma once

#include "world/World.h"

#include <glm/vec3.hpp>

namespace world
{
	namespace io
	{
		class RegionSaver
		{
		public:
			void write(const World & world, const glm::ivec3 & rpos) const;
		};
	}
}