
#include "ChunkData.h"

#include <glm/vec4.hpp>
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
	const glm::uvec4 currentLight{ m_colors[index].getColor(), m_blocks[index].getLight() };
	const glm::uvec4 newLight{ color.getColor(), block.getLight() };

	if (currentLight.x > newLight.x || currentLight.y > newLight.y || currentLight.z > newLight.z || currentLight.a > newLight.a)
		pushLightRemoval(index);
	else if (currentLight.x < newLight.x || currentLight.y < newLight.y || currentLight.z < newLight.z || currentLight.a < newLight.a)
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