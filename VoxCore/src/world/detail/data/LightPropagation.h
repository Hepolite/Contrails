
#pragma once

#include "world/detail/data/Indexing.h"
#include "world/util/Side.h"

#include <glm/vec3.hpp>

namespace world
{
	class Chunk;
	class World;

	namespace data
	{
		constexpr unsigned int LIGHT_PROPAGATION_CHANNEL_COLOR = 0u;
		constexpr unsigned int LIGHT_PROPAGATION_CHANNEL_RED = 0u;
		constexpr unsigned int LIGHT_PROPAGATION_CHANNEL_GREEN = 0u;
		constexpr unsigned int LIGHT_PROPAGATION_CHANNEL_BLUE = 0u;
		constexpr unsigned int LIGHT_PROPAGATION_CHANNEL_SUN = 3u;
		constexpr unsigned int LIGHT_PROPAGATION_CHANNEL_COUNT = 4u;

		struct LightPropagationNode
		{
			Index m_index;
			unsigned int m_light;
		};

		class LightSpreaderBase
		{
		public:
			LightSpreaderBase() = delete;
			LightSpreaderBase(World & world, const glm::ivec3 pos) noexcept : m_world(&world), m_pos(pos) {}
			virtual ~LightSpreaderBase() noexcept = default;

		protected:
			World * m_world;
			glm::ivec3 m_pos;
		};

		class LightSunPropagator : public LightSpreaderBase
		{
		public:
			LightSunPropagator() = delete;
			LightSunPropagator(World & world, const glm::ivec3 pos) noexcept : LightSpreaderBase(world, pos) {}

			void spread(Chunk & chunk);
			void spreadFrom(Chunk & chunk, const glm::ivec3 & source, unsigned int light);
			void spreadDown(Chunk & chunk, const glm::ivec3 & target, unsigned int light);
			void spreadSide(Chunk & chunk, const glm::ivec3 & target, unsigned int light);
		};
		class LightSunRemover : public LightSpreaderBase
		{
		public:
			LightSunRemover() = delete;
			LightSunRemover(World & world, const glm::ivec3 pos) noexcept : LightSpreaderBase(world, pos) {}

			void spread(Chunk & chunk);
			void spreadFrom(Chunk & chunk, const glm::ivec3 & source, unsigned int light);
			void spreadDown(Chunk & chunk, const glm::ivec3 & target, unsigned int light);
			void spreadSide(Chunk & chunk, const glm::ivec3 & target, unsigned int light);
		};

		class LightColorPropagator
		{
		public:


		private:

		};
		class LightColorRemover
		{
		public:


		private:

		};
	}
}