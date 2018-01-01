
#pragma once

#include "world/detail/Limits.h"

#include <glm/vec3.hpp>
#include <stdint.h>

namespace world
{
	namespace data
	{
		using Index = uint16_t;

		template<typename T>
		constexpr Index toIndex(const glm::tvec3<T> & pos)
		{
			return (pos.z * CHUNK_SIZE<T> + pos.y) * CHUNK_SIZE<T> + pos.x;
		}
		template<typename T>
		constexpr glm::tvec3<T> toPos(Index index)
		{
			return glm::tvec3<T>{
				index % CHUNK_SIZE<T>,
				(index / CHUNK_SIZE<T>) % CHUNK_SIZE<T>,
				index / (CHUNK_SIZE<T> * CHUNK_SIZE<T>)
			};
		}
	}
}
