
#include "Chunk.h"

#include "world/detail/data/ChunkData.h"
#include "world/detail/data/ChunkDataTranslator.h"
#include "world/detail/data/ChunkQuery.h"
#include "world/detail/data/Indexing.h"

world::Chunk::Chunk() = default;
world::Chunk::~Chunk() = default;

void world::Chunk::compress()
{
	if (m_compressed != nullptr)
		return;
	if (m_bloated == nullptr)
		m_compressed = std::make_unique<data::ChunkDataCompressed>();
	else
		m_compressed = std::make_unique<data::ChunkDataCompressed>(data::ChunkDataTranslator::compress(*m_bloated));
	m_bloated = nullptr;
}
void world::Chunk::expand()
{
	if (m_bloated != nullptr)
		return;
	if (m_compressed == nullptr)
		m_bloated = std::make_unique<data::ChunkDataBloated>();
	else
		m_bloated = std::make_unique<data::ChunkDataBloated>(data::ChunkDataTranslator::expand(*m_compressed));
	m_compressed = nullptr;
}

void world::Chunk::setFastUnsafe(unsigned int index, const data::BlockData & block, const data::ColorData & color)
{
	expand();
	m_bloated->setFastUnsafe(index, block, color);
}
void world::Chunk::setFastUnsafe(unsigned int index, const data::BlockData & block)
{
	expand();
	m_bloated->setFastUnsafe(index, block);
}
void world::Chunk::setFastUnsafe(unsigned int index, const data::ColorData & color)
{
	expand();
	m_bloated->setFastUnsafe(index, color);
}
void world::Chunk::write(data::ChunkQuery & query)
{
	expand();
	m_bloated->write(query);
}
void world::Chunk::write(unsigned int index, data::BlockData & block, data::ColorData & color)
{
	expand();
	m_bloated->write(index, block, color);
}
void world::Chunk::write(unsigned int index, data::BlockData & block)
{
	expand();
	m_bloated->write(index, block);
}
void world::Chunk::write(unsigned int index, data::ColorData & color)
{
	expand();
	m_bloated->write(index, color);
}
void world::Chunk::read(data::ChunkQuery & query) const
{
	if (m_compressed != nullptr)
		return m_compressed->read(query);
	if (m_bloated != nullptr)
		return m_bloated->read(query);
}
void world::Chunk::read(data::BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const
{
	if (m_compressed != nullptr)
		return m_compressed->read(region, source, target, size);
	if (m_bloated != nullptr)
		return m_bloated->read(region, source, target, size);
}
world::data::BlockData world::Chunk::readBlock(unsigned int index) const
{
	if (m_compressed != nullptr)
		return m_compressed->readBlock(index);
	if (m_bloated != nullptr)
		return m_bloated->readBlock(index);
	return {};
}
world::data::ColorData world::Chunk::readColor(unsigned int index) const
{
	if (m_compressed != nullptr)
		return m_compressed->readColor(index);
	if (m_bloated != nullptr)
		return m_bloated->readColor(index);
	return {};
}
world::data::ChunkDataCompressed world::Chunk::readData() const
{
	if (m_compressed != nullptr)
		return *m_compressed;
	if (m_bloated != nullptr)
		return data::ChunkDataTranslator::compress(*m_bloated);
	return {};
}

bool world::Chunk::pollLightPropagation(data::LightPropagationNode & node, unsigned int channel)
{
	if (m_bloated == nullptr)
		return false;
	return m_bloated->pollLightPropagation(node, channel);
}
void world::Chunk::pushLightPropagation(const data::LightPropagationNode & node, unsigned int channel)
{
	expand();
	m_bloated->pushLightPropagation(node, channel);
}
bool world::Chunk::pollLightRemoval(data::LightPropagationNode & node, unsigned int channel)
{
	if (m_bloated == nullptr)
		return false;
	return m_bloated->pollLightRemoval(node, channel);
}
void world::Chunk::pushLightRemoval(const data::LightPropagationNode & node, unsigned int channel)
{
	expand();
	m_bloated->pushLightRemoval(node, channel);
}

bool world::Chunk::empty() const
{
	if (m_bloated != nullptr)
		return m_bloated->empty();
	if (m_compressed != nullptr)
		return m_compressed->empty();
	return true;
}
