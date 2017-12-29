
#pragma once

#include "world/data/BlockData.h"
#include "world/data/ChunkQuery.h"
#include "world/data/Limits.h"
#include "world/data/Indexing.h"

#include <array>
#include <vector>
#include <queue>

namespace world
{
	namespace data
	{
		template<typename T>
		struct ChunkDataNode
		{
			Index m_index;
			T m_data;
		};
		using ChunkBlockDataNode = ChunkDataNode<BlockData>;
		using ChunkColorDataNode = ChunkDataNode<ColorData>;

		class ChunkDataBloated
		{
		public:
			void write(ChunkQuery & query);
			void write(unsigned int index, BlockData & block, ColorData & color);
			void read(ChunkQuery & query) const;
			void read(unsigned int index, BlockData & block, ColorData & color) const;
			// void read(BlockRegion & region, const glm::ivec3 & offset, const glm::uvec3 & size) const;

			bool pollLightPropagation(Index & index);
			void pushLightPropagation(Index index);
			bool pollLightRemoval(Index & index);
			void pushLightRemoval(Index index);

		private:
			std::array<BlockData, CHUNK_SIZE_VOLUME<unsigned int>> m_blocks;
			std::array<ColorData, CHUNK_SIZE_VOLUME<unsigned int>> m_colors;
			std::queue<Index> m_lightPropagation, m_lightRemoval;
		};

		class ChunkDataCompressed
		{
		public:
			void read(ChunkQuery & query) const;
			void read(unsigned int index, BlockData & block, ColorData & color) const;
			// void read(BlockRegion & region, const glm::ivec3 & offset, const glm::uvec3 & size) const;

			void pushLightPropagation(Index index);
			void pushLightRemoval(Index index);

		private:
			std::vector<ChunkBlockDataNode> m_blocks;
			std::vector<ChunkColorDataNode> m_colors;
			std::queue<Index> m_lightPropagation, m_lightRemoval;
		};
	}
}