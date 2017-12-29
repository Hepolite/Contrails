
#include "ChunkData.h"

#include <utility>

void world::data::ChunkDataBloated::read(ChunkQuery & query) const
{
	for (auto & it : query)
		read(it.m_index, it.m_block, it.m_color);
}
void world::data::ChunkDataBloated::read(unsigned int index, BlockData & block, ColorData & color) const
{
	block = m_blocks[index];
	color = m_colors[index];
}
void world::data::ChunkDataBloated::write(ChunkQuery & query)
{
	for (auto & it : query)
		write(it.m_index, it.m_block, it.m_color);
}
void world::data::ChunkDataBloated::write(unsigned int index, BlockData & block, ColorData & color)
{
	if (m_blocks[index].getLight() != 0u || m_colors[index].getData() != 0u)
		pushLightRemoval(index);
	if (block.getLight() != 0u || color.getData() != 0u)
		pushLightPropagation(index);

	std::swap(m_blocks[index], block);
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
void world::data::ChunkDataBloated::pushLightPropagation(Index index)
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
void world::data::ChunkDataBloated::pushLightRemoval(Index index)
{
	m_lightRemoval.push(index);
}