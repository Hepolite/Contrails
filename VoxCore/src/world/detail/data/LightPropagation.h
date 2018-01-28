
#pragma once

#include "world/detail/data/Indexing.h"

#include <glm/vec3.hpp>

namespace world
{
	class Chunk;
	class World;

	namespace data
	{
		struct LightPropagationNode
		{
			Index m_index;
			unsigned int m_light;
		};
	}
}