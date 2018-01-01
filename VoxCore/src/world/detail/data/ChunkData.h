
#pragma once

#include "world/detail/data/BlockData.h"
#include "world/detail/data/Indexing.h"
#include "world/detail/Limits.h"

#include <array>
#include <vector>
#include <queue>

namespace world
{
	namespace data
	{
		class ChunkQuery;

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
			void write(unsigned int index, BlockData & block);
			void write(unsigned int index, ColorData & color);
			void read(ChunkQuery & query) const;
			// void read(BlockRegion & region, const glm::ivec3 & offset, const glm::uvec3 & size) const;
			BlockData readBlock(unsigned int index) const;
			ColorData readColor(unsigned int index) const;

			bool pollLightPropagation(Index & index);
			void pushLightPropagation(const Index & index);
			bool pollLightRemoval(Index & index);
			void pushLightRemoval(const Index & index);

		private:
			std::array<BlockData, CHUNK_SIZE_VOLUME<unsigned int>> m_blocks;
			std::array<ColorData, CHUNK_SIZE_VOLUME<unsigned int>> m_colors;
			std::queue<Index> m_lightPropagation, m_lightRemoval;
		};

		class ChunkDataCompressed
		{
		public:
			void read(ChunkQuery & query) const;
			// void read(BlockRegion & region, const glm::ivec3 & offset, const glm::uvec3 & size) const;
			BlockData readBlock(unsigned int index) const;
			ColorData readColor(unsigned int index) const;

			void pushLightPropagation(const Index & index);
			void pushLightRemoval(const Index & index);

		private:
			std::vector<ChunkBlockDataNode> m_blocks;
			std::vector<ChunkColorDataNode> m_colors;
			std::queue<Index> m_lightPropagation, m_lightRemoval;
		};
	}
}