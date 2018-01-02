
#pragma once

#include "world/detail/data/ChunkData.h"

namespace world
{
	namespace data
	{
		class BlockData;
		class BlockRegion;
		class ColorData;
		class ChunkQuery;
	}

	class Chunk
	{
	public:
		void write(data::ChunkQuery & query);
		void write(unsigned int index, data::BlockData & block, data::ColorData & color);
		void write(unsigned int index, data::BlockData & block);
		void write(unsigned int index, data::ColorData & color);
		void read(data::ChunkQuery & query) const;
		void read(data::BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const;
		data::BlockData readBlock(unsigned int index) const;
		data::ColorData readColor(unsigned int index) const;

		bool pollLightPropagation(data::Index & index);
		void pushLightPropagation(const data::Index & index);
		bool pollLightRemoval(data::Index & index);
		void pushLightRemoval(const data::Index & index);

	private:
		data::ChunkDataBloated m_data;
	};
}