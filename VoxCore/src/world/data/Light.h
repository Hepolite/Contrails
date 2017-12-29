
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "world/World.h"

#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <unordered_set>

namespace world
{
	namespace data
	{
		class LightPropagator
		{
		public:
			// LightPropagator() = delete;
			// LightPropagator(World * world, const glm::ivec3 & cpos) noexcept;

			void process();

		private:
			// std::unordered_set<glm::ivec3> m_chunks;
		};
	}
}