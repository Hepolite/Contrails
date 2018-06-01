
#pragma once

#include "world/detail/data/ChunkData.h"

#include <glm/vec3.hpp>

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
		void setFastUnsafe(unsigned int index, const data::BlockData & block, const data::ColorData & color);
		void setFastUnsafe(unsigned int index, const data::BlockData & block);
		void setFastUnsafe(unsigned int index, const data::ColorData & color);
		void write(data::ChunkQuery & query);
		void write(unsigned int index, data::BlockData & block, data::ColorData & color);
		void write(unsigned int index, data::BlockData & block);
		void write(unsigned int index, data::ColorData & color);
		void read(data::ChunkQuery & query) const;
		void read(data::BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const;
		data::BlockData readBlock(unsigned int index) const;
		data::ColorData readColor(unsigned int index) const;

		bool pollLightPropagation(data::LightPropagationNode & node, unsigned int channel);
		void pushLightPropagation(const data::LightPropagationNode & node, unsigned int channel);
		bool pollLightRemoval(data::LightPropagationNode & node, unsigned int channel);
		void pushLightRemoval(const data::LightPropagationNode & node, unsigned int channel);

		bool empty() const;

	private:
		data::ChunkDataBloated m_data;
	};
}