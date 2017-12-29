
#pragma once

#include "world/data/ChunkData.h"
#include "world/data/ChunkQuery.h"

namespace world
{
	struct Chunk
	{
	public:
		void write(data::ChunkQuery & query);
		void write(const glm::uvec3 & pos, data::BlockData & block, data::ColorData & color);
		void read(data::ChunkQuery & query) const;
		void read(const glm::uvec3 & pos, data::BlockData & block, data::ColorData & color) const;

	private:
		data::ChunkDataBloated m_data;
	};
}