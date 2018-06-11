
#pragma once

#include "world/detail/data/BlockData.h"
#include "world/detail/data/Indexing.h"
#include "world/detail/data/LightPropagation.h"
#include "world/detail/Limits.h"

#include <array>
#include <vector>
#include <queue>

namespace world
{
	namespace data
	{
		class BlockRegion;
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
			void setFastUnsafe(Index index, const BlockData & block, const ColorData & color);
			void setFastUnsafe(Index index, const BlockData & block);
			void setFastUnsafe(Index index, const ColorData & color);
			BlockData getBlockFastUnsafe(Index index) const;
			ColorData getColorFastUnsafe(Index index) const;

			void write(ChunkQuery & query);
			void write(Index index, BlockData & block, ColorData & color);
			void write(Index index, BlockData & block);
			void write(Index index, ColorData & color);
			void read(ChunkQuery & query) const;
			void read(BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const;
			BlockData readBlock(Index index) const;
			ColorData readColor(Index index) const;

			bool pollLightPropagation(LightPropagationNode & node, unsigned int channel);
			void pushLightPropagation(const LightPropagationNode & node, unsigned int channel);
			bool pollLightRemoval(LightPropagationNode & node, unsigned int channel);
			void pushLightRemoval(const LightPropagationNode & node, unsigned int channel);

			bool empty() const;
			bool light() const;

		private:
			std::array<BlockData, CHUNK_SIZE_VOLUME<unsigned int>> m_blocks;
			std::array<ColorData, CHUNK_SIZE_VOLUME<unsigned int>> m_colors;
			std::queue<LightPropagationNode> m_lightPropagation[LIGHT_PROPAGATION_CHANNEL_COUNT];
			std::queue<LightPropagationNode> m_lightRemoval[LIGHT_PROPAGATION_CHANNEL_COUNT];
		};

		class ChunkDataCompressed
		{
			friend class ChunkDataTranslator;

		public:
			void read(ChunkQuery & query) const;
			void read(BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const;
			inline BlockData readBlock(Index index) const { return find(index, m_blocks); }
			inline ColorData readColor(Index index) const { return find(index, m_colors); }

			bool empty() const;

		private:
			template<typename T> inline T find(Index index, const std::vector<ChunkDataNode<T>> & data) const;

			std::vector<ChunkBlockDataNode> m_blocks;
			std::vector<ChunkColorDataNode> m_colors;
		};
	}
}

template<typename T>
inline T world::data::ChunkDataCompressed::find(Index index, const std::vector<ChunkDataNode<T>>& data) const
{
	const auto it = std::lower_bound(data.begin(), data.end(), index,
		[](const auto & lhs, const auto & rhs) { return lhs.m_index < rhs; }
	);
	return it == data.end() ? T{} : it->m_data;
}