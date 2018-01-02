
#include "ChunkData.h"

#include "util/Maths.h"
#include "world/detail/data/BlockRegion.h"
#include "world/detail/data/ChunkQuery.h"

#include <glm/vec4.hpp>
#include <utility>

void world::data::ChunkDataBloated::read(ChunkQuery & query) const
{
	for (auto & it : query)
	{
		it.m_block = readBlock(it.m_index);
		it.m_color = readColor(it.m_index);
	}
}
void world::data::ChunkDataBloated::read(BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const
{
	glm::ivec3 pos;
	for (pos.x = 0; pos.x < size.x; ++pos.x)
	for (pos.y = 0; pos.y < size.y; ++pos.y)
	for (pos.z = 0; pos.z < size.z; ++pos.z)
	{
		const auto index = toIndex(pos + source);
		region.write(pos + target, readBlock(index), readColor(index));
	}
}
world::data::BlockData world::data::ChunkDataBloated::readBlock(unsigned int index) const
{
	return index < m_blocks.size() ? m_blocks[index] : BlockData{};
}
world::data::ColorData world::data::ChunkDataBloated::readColor(unsigned int index) const
{
	return index < m_colors.size() ? m_colors[index] : ColorData{};
}

void world::data::ChunkDataBloated::write(ChunkQuery & query)
{
	for (auto & it : query)
	{
		write(it.m_index, it.m_block);
		write(it.m_index, it.m_color);
	}
}
void world::data::ChunkDataBloated::write(unsigned int index, BlockData & block, ColorData & color)
{
	write(index, block);
	write(index, color);
}
void world::data::ChunkDataBloated::write(unsigned int index, BlockData & block)
{
	const auto oldLight = readBlock(index).getLight();
	const auto newLight = block.getLight();

	if (oldLight > newLight)
		pushLightRemoval(index);
	else if (oldLight < newLight)
		pushLightPropagation(index);

	std::swap(m_blocks[index], block);
}
void world::data::ChunkDataBloated::write(unsigned int index, ColorData & color)
{
	const auto oldLight = readColor(index).getColor();
	const auto newLight = color.getColor();

	if (oldLight.x > newLight.x || oldLight.y > newLight.y || oldLight.z > newLight.z)
		pushLightRemoval(index);
	else if (oldLight.x < newLight.x || oldLight.y < newLight.y || oldLight.z < newLight.z)
		pushLightPropagation(index);

	std::swap(m_colors[index], color);
}

bool world::data::ChunkDataBloated::pollLightPropagation(Index & index)
{
	if (m_lightPropagation.empty())
		return false;
	index = m_lightPropagation.front();
	m_lightPropagation.pop();
	return true;
}
void world::data::ChunkDataBloated::pushLightPropagation(const Index & index)
{
	m_lightPropagation.push(index);
}
bool world::data::ChunkDataBloated::pollLightRemoval(Index & index)
{
	if (m_lightRemoval.empty())
		return false;
	index = m_lightRemoval.front();
	m_lightRemoval.pop();
	return true;
}
void world::data::ChunkDataBloated::pushLightRemoval(const Index & index)
{
	m_lightRemoval.push(index);
}