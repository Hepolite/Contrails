
#include "Chunk.h"

#include "world/data/Indexing.h"

void world::Chunk::write(data::ChunkQuery & query)
{
	m_data.write(query);
}
void world::Chunk::write(const data::Index & index, data::BlockData & block, data::ColorData & color)
{
	m_data.write(index, block, color);
}
void world::Chunk::write(const glm::uvec3 & pos, data::BlockData & block, data::ColorData & color)
{
	m_data.write(data::toIndex(pos), block, color);
}
void world::Chunk::read(data::ChunkQuery & query) const
{
	m_data.read(query);
}
void world::Chunk::read(const data::Index & index, data::BlockData & block, data::ColorData & color) const
{
	m_data.read(index, block, color);
}
void world::Chunk::read(const glm::uvec3 & pos, data::BlockData & block, data::ColorData & color) const
{
	m_data.read(data::toIndex(pos), block, color);
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
