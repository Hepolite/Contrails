
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "world/detail/data/ChunkQuery.h"

#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

namespace world
{
	namespace data
	{
		class WorldQuery
		{
		public:
			WorldQuery() = default;
			WorldQuery(const WorldQuery &) = delete;
			WorldQuery(WorldQuery &&) = default;
			~WorldQuery() = default;

			WorldQuery & operator=(const WorldQuery &) = delete;
			WorldQuery & operator=(WorldQuery &&) = default;

			inline auto empty() const { return m_data.empty(); }
			inline auto size() const { return m_data.size(); }
			inline auto begin() { return m_data.begin(); }
			inline auto begin() const { return m_data.begin(); }
			inline auto end() { return m_data.end(); }
			inline auto end() const { return m_data.end(); }
			inline auto memuse() const { return m_memuse; }

			void add(const glm::ivec3 & cpos, ChunkQuery && query);
			void add(const glm::ivec3 & pos);
			void add(const glm::ivec3 & pos, const BlockData & block, const ColorData & color = {});

		private:
			std::unordered_map<glm::ivec3, ChunkQuery> m_data;

			unsigned int m_memuse = 0u;
		};
	}
}