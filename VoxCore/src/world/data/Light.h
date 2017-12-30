
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <unordered_set>

namespace world
{
	class Chunk;
	class World;

	namespace data
	{
		class LightPropagator
		{
		public:
			LightPropagator() = delete;
			LightPropagator(World & world, const glm::ivec3 & cpos) noexcept;
			LightPropagator(const LightPropagator &) noexcept = default;
			LightPropagator(LightPropagator &&) noexcept = default;
			~LightPropagator() noexcept = default;

			LightPropagator & operator=(const LightPropagator &) noexcept = default;
			LightPropagator & operator=(LightPropagator &&) noexcept = default;

			void propagate() const;
			void propagateFrom(Chunk & chunk, const glm::uvec3 & source, glm::uvec4 light) const;
			void propagateTo(Chunk & chunk, const glm::uvec3 & target, glm::uvec4 light) const;

		private:
			World * m_world = nullptr;
			glm::ivec3 m_cpos{};
		};
	}
}