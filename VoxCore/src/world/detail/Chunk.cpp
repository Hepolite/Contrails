
#include "Chunk.h"

#include "world/detail/data/ChunkQuery.h"
#include "world/detail/data/Indexing.h"

void world::Chunk::setFastUnsafe(unsigned int index, const data::BlockData & block, const data::ColorData & color)
{
	m_data.setFastUnsafe(index, block, color);
}
void world::Chunk::setFastUnsafe(unsigned int index, const data::BlockData & block)
{
	m_data.setFastUnsafe(index, block);
}
void world::Chunk::setFastUnsafe(unsigned int index, const data::ColorData & color)
{
	m_data.setFastUnsafe(index, color);
}
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

bool world::Chunk::pollLightPropagation(data::LightPropagationNode & node, unsigned int channel)
{
	return m_data.pollLightPropagation(node, channel);
}
void world::Chunk::pushLightPropagation(const data::LightPropagationNode & node, unsigned int channel)
{
	m_data.pushLightPropagation(node, channel);
}
bool world::Chunk::pollLightRemoval(data::LightPropagationNode & node, unsigned int channel)
{
	return m_data.pollLightRemoval(node, channel);
}
void world::Chunk::pushLightRemoval(const data::LightPropagationNode & node, unsigned int channel)
{
	m_data.pushLightRemoval(node, channel);
}

bool world::Chunk::empty() const
{
	return m_data.empty();
}
