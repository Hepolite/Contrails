
#include "Chunk.h"

#include "world/detail/data/ChunkQuery.h"
#include "world/detail/data/Indexing.h"

void world::Chunk::write(data::ChunkQuery & query)
{
	m_data.write(query);
}
void world::Chunk::write(unsigned int index, data::BlockData & block, data::ColorData & color)
{
	m_data.write(index, block, color);
}
void world::Chunk::write(unsigned int index, data::BlockData & block)
{
	m_data.write(index, block);
}
void world::Chunk::write(unsigned int index, data::ColorData & color)
{
	m_data.write(index, color);
}
void world::Chunk::read(data::ChunkQuery & query) const
{
	m_data.read(query);
}
void world::Chunk::read(data::BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const
{
	m_data.read(region, source, target, size);
}
world::data::BlockData world::Chunk::readBlock(unsigned int index) const
{
	return m_data.readBlock(index);
}
world::data::ColorData world::Chunk::readColor(unsigned int index) const
{
	return m_data.readColor(index);
}

bool world::Chunk::pollLightPropagation(data::Index & index)
{
	return m_data.pollLightPropagation(index);
}
void world::Chunk::pushLightPropagation(const data::Index & index)
{
	m_data.pushLightPropagation(index);
}
bool world::Chunk::pollLightRemoval(data::Index & index)
{
	return m_data.pollLightRemoval(index);
}
void world::Chunk::pushLightRemoval(const data::Index & index)
{
	m_data.pushLightRemoval(index);
}
