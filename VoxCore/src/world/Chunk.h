
#pragma once

#include "world/data/ChunkData.h"
#include "world/data/ChunkQuery.h"

namespace world
{
	class Chunk
	{
	public:
		void write(data::ChunkQuery & query);
		void write(const data::Index & index, data::BlockData & block, data::ColorData & color);
		void write(const glm::uvec3 & pos, data::BlockData & block, data::ColorData & color);
		void read(data::ChunkQuery & query) const;
		void read(const data::Index & index, data::BlockData & block, data::ColorData & color) const;
		void read(const glm::uvec3 & pos, data::BlockData & block, data::ColorData & color) const;

		bool pollLightPropagation(data::Index & index);
		void pushLightPropagation(const data::Index & index);
		bool pollLightRemoval(data::Index & index);
		void pushLightRemoval(const data::Index & index);

	private:
		data::ChunkDataBloated m_data;
	};
}