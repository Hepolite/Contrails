
#include "ChunkData.h"

#include "util/Maths.h"
#include "world/detail/data/BlockRegion.h"
#include "world/detail/data/ChunkQuery.h"

#include <algorithm>
#include <glm/vec4.hpp>
#include <utility>

void world::data::ChunkDataBloated::setFastUnsafe(Index index, const BlockData & block, const ColorData & color)
{
	m_blocks[index] = block;
	m_colors[index] = color;
}
void world::data::ChunkDataBloated::setFastUnsafe(Index index, const BlockData & block)
{
	m_blocks[index] = block;
}
void world::data::ChunkDataBloated::setFastUnsafe(Index index, const ColorData & color)
{
	m_colors[index] = color;
}
world::data::BlockData world::data::ChunkDataBloated::getBlockFastUnsafe(Index index) const
{
	return m_blocks[index];
}
world::data::ColorData world::data::ChunkDataBloated::getColorFastUnsafe(Index index) const
{
	return m_colors[index];
}

void world::data::ChunkDataBloated::write(ChunkQuery & query)
{
	for (auto & it : query)
		write(it.m_index, it.m_block, it.m_color);
}
void world::data::ChunkDataBloated::write(Index index, BlockData & block, ColorData & color)
{
	write(index, block);
	write(index, color);
}
void world::data::ChunkDataBloated::write(Index index, BlockData & block)
{
	const auto oldLight = readBlock(index).getLight();
	const auto newLight = block.getLight();

	pushLightRemoval({ index, oldLight }, LIGHT_PROPAGATION_CHANNEL_SUN);
	if (newLight != 0u)
		pushLightPropagation({ index, newLight }, LIGHT_PROPAGATION_CHANNEL_SUN);

	std::swap(m_blocks[index], block);
}
void world::data::ChunkDataBloated::write(Index index, ColorData & color)
{
	const auto oldLight = readColor(index).getColor();
	const auto newLight = color.getColor();

	unsigned int propagate = 0u;
	unsigned int remove = 0u;
	if		(oldLight.r > newLight.r) remove |= oldLight.r << 16u;
	else if (newLight.r > oldLight.r) propagate |= newLight.r << 16u;
	if		(oldLight.g > newLight.g) remove |= oldLight.g << 8u;
	else if (newLight.g > oldLight.g) propagate |= newLight.g << 8u;
	if		(oldLight.b > newLight.b) remove |= oldLight.b;
	else if (newLight.b > oldLight.b) propagate |= newLight.b;
	if (propagate != 0u)
		pushLightPropagation({ index, propagate }, LIGHT_PROPAGATION_CHANNEL_COLOR);
	if (remove != 0u)
		pushLightRemoval({ index, remove }, LIGHT_PROPAGATION_CHANNEL_COLOR);

	std::swap(m_colors[index], color);
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

bool world::data::ChunkDataBloated::pollLightPropagation(LightPropagationNode & node, unsigned int channel)
{
	if (channel >= LIGHT_PROPAGATION_CHANNEL_COUNT || m_lightPropagation[channel].empty())
		return false;
	node = m_lightPropagation[channel].front();
	m_lightPropagation[channel].pop();
	return true;
}
void world::data::ChunkDataBloated::pushLightPropagation(const LightPropagationNode & node, unsigned int channel)
{
	if (channel < LIGHT_PROPAGATION_CHANNEL_COUNT)
		m_lightPropagation[channel].push(node);
}
bool world::data::ChunkDataBloated::pollLightRemoval(LightPropagationNode & node, unsigned int channel)
{
	if (channel >= LIGHT_PROPAGATION_CHANNEL_COUNT || m_lightRemoval[channel].empty())
		return false;
	node = m_lightRemoval[channel].front();
	m_lightRemoval[channel].pop();
	return true;
}
void world::data::ChunkDataBloated::pushLightRemoval(const LightPropagationNode & node, unsigned int channel)
{
	if (channel < LIGHT_PROPAGATION_CHANNEL_COUNT)
		m_lightRemoval[channel].push(node);
}

bool world::data::ChunkDataBloated::empty() const
{
	for (const auto & data : m_blocks)
	{
		if (data.getId() != 0u)
			return false;
	}
	return true;
}
bool world::data::ChunkDataBloated::light() const
{
	for (unsigned int i = 0u; i < LIGHT_PROPAGATION_CHANNEL_COUNT; ++i)
	{
		if (!m_lightPropagation[i].empty() || !m_lightRemoval[i].empty())
			return true;
	}
	return false;
}

// ...

void world::data::ChunkDataCompressed::read(ChunkQuery & query) const
{
	for (auto & it : query)
	{
		it.m_block = readBlock(it.m_index);
		it.m_color = readColor(it.m_index);
	}
}
void world::data::ChunkDataCompressed::read(BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const
{
	if (source == glm::ivec3{} && size == glm::ivec3{ CHUNK_SIZE<int> })
	{
		const auto min = target;
		const auto max = target + size;

		ChunkBlockDataNode blockNode{};
		ChunkColorDataNode colorNode{};
		unsigned int index = 0u;

		glm::ivec3 pos;
		for (pos.z = min.z; pos.z < max.z; ++pos.z)
		for (pos.y = min.y; pos.y < max.y; ++pos.y)
		for (pos.x = min.x; pos.x < max.x; ++pos.x)
		{
			const auto & block = m_blocks.at(blockNode.m_index);
			const auto & color = m_colors.at(colorNode.m_index);
			region.write(pos + target, block.m_data, color.m_data);
			
			++index;
			if (index > block.m_index)
				++blockNode.m_index;
			if (index > color.m_index)
				++colorNode.m_index;
		}
	}
	else
	{
		glm::ivec3 pos;
		for (pos.z = 0; pos.z < size.z; ++pos.z)
		for (pos.y = 0; pos.y < size.y; ++pos.y)
		for (pos.x = 0; pos.x < size.x; ++pos.x)
		{
			const auto index = toIndex(pos + source);
			region.write(pos + target, readBlock(index), readColor(index));
		}
	}
}

bool world::data::ChunkDataCompressed::empty() const
{
	return m_blocks.empty() || (m_blocks.size() == 1u && m_blocks.front().m_data.getId() == 0u);
}
