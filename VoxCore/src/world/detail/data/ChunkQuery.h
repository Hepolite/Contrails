
#pragma once

#include "world/detail/data/BlockData.h"
#include "world/detail/data/Indexing.h"

#include <glm/vec3.hpp>
#include <vector>

namespace world
{
	namespace data
	{
		struct QueryDataNode
		{
			Index m_index;
			BlockData m_block;
			ColorData m_color;
		};

		class ChunkQuery
		{
		public:
			ChunkQuery() noexcept = default;
			ChunkQuery(const ChunkQuery &) = delete;
			ChunkQuery(ChunkQuery &&) noexcept = default;
			~ChunkQuery() noexcept = default;

			ChunkQuery & operator=(const ChunkQuery &) = delete;
			ChunkQuery & operator=(ChunkQuery &&) noexcept = default;

			inline auto memuse() const { return m_data.capacity() * sizeof(QueryDataNode); }
			inline auto empty() const { return m_data.empty(); }
			inline auto size() const { return m_data.size(); }
			inline auto begin() { return m_data.begin(); }
			inline auto begin() const { return m_data.begin(); }
			inline auto end() { return m_data.end(); }
			inline auto end() const { return m_data.end(); }

			inline auto min() const { return m_min; }
			inline auto max() const { return m_max; }

			void add(const glm::uvec3 & pos);
			void add(const glm::uvec3 & pos, const BlockData & block, const ColorData & color = {});
			void add(const glm::uvec3 & start, const glm::uvec3 & end);
			void add(const glm::uvec3 & start, const glm::uvec3 & end, const BlockData & block, const ColorData & color = {});

			bool has(const glm::uvec3 & pos) const;

		private:
			void inject(Index index, const BlockData & block, const ColorData & color);
			void updateBounds(const glm::uvec3 & start, const glm::uvec3 & end);

			std::vector<QueryDataNode> m_data;
			glm::uvec3 m_min, m_max;
		};
	}
}