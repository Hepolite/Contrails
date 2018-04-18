
#pragma once

#include "world/detail/Block.h"

#include <glm/vec3.hpp>

namespace world
{
	class World;

	namespace util
	{
		class Raytrace
		{
		public:
			Raytrace() = delete;
			Raytrace(const World & world, const glm::ivec3 & start, const glm::ivec3 & end);
			Raytrace(const World & world, const glm::vec3 & start, const glm::vec3 & end);
			Raytrace(const World & world, const glm::vec3 & start, const glm::vec3 & dir, float length);
			Raytrace(const Raytrace &) = default;
			Raytrace(Raytrace &&) = default;
			~Raytrace() = default;

			Raytrace & operator=(const Raytrace &) = default;
			Raytrace & operator=(Raytrace &&) = default;

			bool isValid() const;

			void next();
			inline auto nextBlock() { next(); return getBlock(); }
			inline auto nextPos() { next(); return getPos(); }
			inline auto nextBlockPos() { next(); return getBlockPos(); }

			unsigned int getBlock() const;
			unsigned int getOldBlock() const;
			glm::vec3 getPos() const;
			glm::vec3 getOldPos() const;
			glm::ivec3 getBlockPos() const;
			glm::ivec3 getOldBlockPos() const;

		private:
			const World & m_world;

			glm::vec3 m_pos, m_oldPos;
			glm::vec3 m_dir;
			glm::vec3 m_step;

			glm::vec3 m_tMax, m_tDelta;
		};

		class RaytraceBresenham
		{
		public:
			RaytraceBresenham() = delete;
			RaytraceBresenham(const World & world, const glm::ivec3 & start, const glm::ivec3 & end);
			RaytraceBresenham(const World & world, const glm::vec3 & start, const glm::vec3 & end);
			RaytraceBresenham(const World & world, const glm::vec3 & start, const glm::vec3 & dir, float length);
			RaytraceBresenham(const RaytraceBresenham &) = default;
			RaytraceBresenham(RaytraceBresenham &&) = default;
			~RaytraceBresenham() = default;

			RaytraceBresenham & operator=(const RaytraceBresenham &) = default;
			RaytraceBresenham & operator=(RaytraceBresenham &&) = default;

			bool isValid() const;

			void next();
			inline auto nextBlock() { next(); return getBlock(); }
			inline auto nextPos() { next(); return getPos(); }

			unsigned int getBlock() const;
			unsigned int getOldBlock() const;
			glm::vec3 getPos() const;
			glm::vec3 getOldPos() const;

		private:
			const World & m_world;

			glm::ivec3 m_pos, m_oldPos;
			glm::ivec3 m_delta;
			glm::ivec3 m_step;
			glm::ivec3 m_error{};

			int m_totalSteps;
			int m_currentStep = 0;
		};
	}
}