
#include "BlockRegion.h"

#include "world/detail/data/Indexing.h"
#include "world/detail/Limits.h"

world::data::BlockRegion::BlockRegion()
	: BlockRegion(glm::ivec3{}, glm::ivec3{ CHUNK_SIZE<int> })
{}
world::data::BlockRegion::BlockRegion(const glm::ivec3 & position, const glm::ivec3 & size)
	: m_pos(position), m_size(size)
{
	m_blocks.resize(m_size.x * m_size.y * m_size.z, {});
	m_colors.resize(m_size.x * m_size.y * m_size.z, {});
}

unsigned int world::data::BlockRegion::memuse() const
{
	return m_blocks.capacity() * sizeof(BlockData) + m_colors.capacity() * sizeof(ColorData);
}

void world::data::BlockRegion::write(const glm::ivec3 & pos, BlockData & block, ColorData & color)
{
	write(pos, block);
	write(pos, color);
}
void world::data::BlockRegion::write(const glm::ivec3 & pos, BlockData & block)
{
	const auto index = toIndex<int>(pos, m_pos, m_size);
	if (index < m_blocks.size())
		m_blocks[index] = block;
}
void world::data::BlockRegion::write(const glm::ivec3 & pos, ColorData & color)
{
	const auto index = toIndex<int>(pos, m_pos, m_size);
	if (index < m_colors.size())
		m_colors[index] = color;
}
world::data::BlockData world::data::BlockRegion::readBlock(const glm::ivec3 & pos) const
{
	const auto index = toIndex<int>(pos, m_pos, m_size);
	return index < m_blocks.size() ? m_blocks[index] : BlockData{};
}
world::data::ColorData world::data::BlockRegion::readColor(const glm::ivec3 & pos) const
{
	const auto index = toIndex<int>(pos, m_pos, m_size);
	return index < m_colors.size() ? m_colors[index] : ColorData{};
}
