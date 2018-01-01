
#include "ChunkQuery.h"

#include "util/Maths.h"

#include <typeinfo>

void world::data::ChunkQuery::add(const glm::uvec3 & pos)
{
	add(pos, BlockData{});
}
void world::data::ChunkQuery::add(const glm::uvec3 & pos, const BlockData & block, const ColorData & color)
{
	updateBounds(pos, pos);
	inject(toIndex(pos), block, color);
}
void world::data::ChunkQuery::add(const glm::uvec3 & start, const glm::uvec3 & end)
{
	add(start, end, BlockData{});
}
void world::data::ChunkQuery::add(const glm::uvec3 & start, const glm::uvec3 & end, const BlockData & block, const ColorData & color)
{
	const auto min = math::min(start, end);
	const auto max = math::max(start, end);
	updateBounds(min, max);

	glm::uvec3 pos;
	for (pos.z = min.z; pos.z <= max.z; ++pos.z)
	for (pos.y = min.y; pos.y <= max.y; ++pos.y)
	for (pos.x = min.x; pos.x <= max.x; ++pos.x)
		inject(toIndex(pos), block, color);
}

void world::data::ChunkQuery::inject(Index index, const BlockData & block, const ColorData & color)
{
	if (index >= CHUNK_SIZE_VOLUME<unsigned int>)
		return;

	if (empty() || m_data.back().m_index < index)
		m_data.push_back({ index, block, color });
	else
	{
		auto it = std::upper_bound(begin(), end(), index,
			[](auto & lhs, auto & rhs) { return lhs <= rhs.m_index; }
		);
		if (it->m_index == index)
		{
			it->m_block = block;
			it->m_color = color;
		}
		else
			m_data.insert(it, { index, block, color });
	}
}

void world::data::ChunkQuery::updateBounds(const glm::uvec3 & start, const glm::uvec3 & end)
{
	const auto min = math::min(start, end);
	const auto max = math::max(start, end);

	if (empty())
	{
		m_min = min;
		m_max = max;
	}
	else
	{
		m_min = math::min(m_min, min);
		m_max = math::max(m_max, max);
	}
}
