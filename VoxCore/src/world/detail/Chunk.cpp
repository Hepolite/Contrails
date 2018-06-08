
#include "Chunk.h"

#include "world/detail/data/ChunkData.h"
#include "world/detail/data/ChunkDataTranslator.h"
#include "world/detail/data/ChunkQuery.h"
#include "world/detail/data/Indexing.h"

world::Chunk::Chunk()
{
	m_bloated = std::make_unique<data::ChunkDataBloated>();
}
world::Chunk::~Chunk() = default;

void world::Chunk::compress()
{
	if (compressed())
		return;
	m_compressed = std::make_unique<data::ChunkDataCompressed>(data::ChunkDataTranslator::compress(*m_bloated));
	m_bloated = nullptr;
}
void world::Chunk::expand()
{
	if (!compressed())
		return;
	m_bloated = std::make_unique<data::ChunkDataBloated>(data::ChunkDataTranslator::expand(*m_compressed));
	m_compressed = nullptr;
}

void world::Chunk::setFastUnsafe(unsigned int index, const data::BlockData & block, const data::ColorData & color)
{
	m_bloated->setFastUnsafe(index, block, color);
}
void world::Chunk::setFastUnsafe(unsigned int index, const data::BlockData & block)
{
	m_bloated->setFastUnsafe(index, block);
}
void world::Chunk::setFastUnsafe(unsigned int index, const data::ColorData & color)
{
	m_bloated->setFastUnsafe(index, color);
}
void world::Chunk::write(data::ChunkQuery & query)
{
	m_bloated->write(query);
}
void world::Chunk::write(unsigned int index, data::BlockData & block, data::ColorData & color)
{
	m_bloated->write(index, block, color);
}
void world::Chunk::write(unsigned int index, data::BlockData & block)
{
	m_bloated->write(index, block);
}
void world::Chunk::write(unsigned int index, data::ColorData & color)
{
	m_bloated->write(index, color);
}
void world::Chunk::read(data::ChunkQuery & query) const
{
	m_bloated->read(query);
}
void world::Chunk::read(data::BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const
{
	m_bloated->read(region, source, target, size);
}
world::data::BlockData world::Chunk::readBlock(unsigned int index) const
{
	return m_bloated->readBlock(index);
}
world::data::ColorData world::Chunk::readColor(unsigned int index) const
{
	return m_bloated->readColor(index);
}
world::data::ChunkDataCompressed world::Chunk::readData() const
{
	return compressed() ? *m_compressed : data::ChunkDataTranslator::compress(*m_bloated);
}

bool world::Chunk::pollLightPropagation(data::LightPropagationNode & node, unsigned int channel)
{
	return m_bloated->pollLightPropagation(node, channel);
}
void world::Chunk::pushLightPropagation(const data::LightPropagationNode & node, unsigned int channel)
{
	m_bloated->pushLightPropagation(node, channel);
}
bool world::Chunk::pollLightRemoval(data::LightPropagationNode & node, unsigned int channel)
{
	return m_bloated->pollLightRemoval(node, channel);
}
void world::Chunk::pushLightRemoval(const data::LightPropagationNode & node, unsigned int channel)
{
	m_bloated->pushLightRemoval(node, channel);
}

bool world::Chunk::empty() const
{
	return m_bloated->empty();
}
bool world::Chunk::compressed() const
{
	return m_compressed != nullptr;
}
