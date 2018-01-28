
#include "ChunkData.h"

#include "util/Maths.h"
#include "world/detail/data/BlockRegion.h"
#include "world/detail/data/ChunkQuery.h"

#include <glm/vec4.hpp>
#include <utility>

namespace
{
	constexpr unsigned int CHANNEL_SUN = 0u;
	constexpr unsigned int CHANNEL_COLOR = 1u;
}

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
world::data::BlockData world::data::ChunkDataBloated::readBlock(Index index) const
{
	return index < m_blocks.size() ? m_blocks[index] : BlockData{};
}
world::data::ColorData world::data::ChunkDataBloated::readColor(Index index) const
{
	return index < m_colors.size() ? m_colors[index] : ColorData{};
}

void world::data::ChunkDataBloated::setFastUnsafe(Index index, const BlockData & block, const ColorData & color)
{
	m_blocks[index] = block;
	m_colors[index] = color;
}
void world::data::ChunkDataBloated::write(ChunkQuery & query)
{
	for (auto & it : query)
		write(it.m_index, it.m_block, it.m_color);
}
void world::data::ChunkDataBloated::write(Index index, BlockData & block, ColorData & color)
{
	const auto oldLight = glm::uvec4{ readBlock(index).getLight(), readColor(index).getColor() };
	const auto newLight = glm::uvec4{ block.getLight(), color.getColor() };

	for (unsigned int i = 0u; i < 4u; ++i)
	{
		if (oldLight[i] > newLight[i])
			pushLightRemoval({ index, oldLight[i] }, i);
		else if (oldLight[i] < newLight[i])
			pushLightPropagation({ index, newLight[i] }, i);
	}
	
	std::swap(m_blocks[index], block);
	std::swap(m_colors[index], color);
}
void world::data::ChunkDataBloated::write(Index index, BlockData & block)
{
	const auto oldLight = readBlock(index).getLight();
	const auto newLight = block.getLight();

	if (oldLight > newLight)
		pushLightRemoval({ index, oldLight }, CHANNEL_SUN);
	else if (oldLight < newLight)
		pushLightPropagation({ index, newLight }, CHANNEL_SUN);

	std::swap(m_blocks[index], block);
}
void world::data::ChunkDataBloated::write(Index index, ColorData & color)
{
	const auto oldLight = readColor(index).getColor();
	const auto newLight = color.getColor();

	for (unsigned int i = 0u; i < 3u; ++i)
	{
		if (oldLight[i] > newLight[i])
			pushLightRemoval({ index, oldLight[i] }, CHANNEL_COLOR + i);
		else if (oldLight[i] < newLight[i])
			pushLightPropagation({ index, newLight[i] }, CHANNEL_COLOR + i);
	}

	std::swap(m_colors[index], color);
}

bool world::data::ChunkDataBloated::pollLightPropagation(LightPropagationNode & node, unsigned int channel)
{
	if (channel >= 4u || m_lightPropagation[channel].empty())
		return false;
	node = m_lightPropagation[channel].front();
	m_lightPropagation[channel].pop();
	return true;
}
void world::data::ChunkDataBloated::pushLightPropagation(const LightPropagationNode & node, unsigned int channel)
{
	if (channel < 4u)
		m_lightPropagation[channel].push(node);
}
bool world::data::ChunkDataBloated::pollLightRemoval(LightPropagationNode & node, unsigned int channel)
{
	if (channel >= 4u || m_lightRemoval[channel].empty())
		return false;
	node = m_lightRemoval[channel].front();
	m_lightRemoval[channel].pop();
	return true;
}
void world::data::ChunkDataBloated::pushLightRemoval(const LightPropagationNode & node, unsigned int channel)
{
	if (channel < 4u)
		m_lightRemoval[channel].push(node);
}
