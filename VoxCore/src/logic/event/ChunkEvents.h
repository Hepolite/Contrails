
#pragma once

#include "world/World.h"

#include <glm/vec3.hpp>

namespace logic
{
	namespace event
	{
		struct ChunkCreate				// A chunk is created for any reason in a world
		{
			world::World * const m_world;	// The world the chunk was created in
			const glm::ivec3 m_cpos;		// The position the chunk was created at
		};
		struct ChunkDestroy				// A chunk is removed for any reason in a world
		{
			world::World * const m_world;	// The world the chunk was destroyed in
			const glm::ivec3 m_cpos;		// The position the chunk was destroyed at
		};

		struct ChunkChange				// A chunk is changed for any reason in a world
		{
			world::World * const m_world;	// the world the chunk was changed in
			const glm::ivec3 m_cpos;		// The position of the chunk
			const glm::uvec3 m_min;			// The minimum position of the chunk change
			const glm::uvec3 m_max;			// The maximum position of the chunk change
		};
	}
}