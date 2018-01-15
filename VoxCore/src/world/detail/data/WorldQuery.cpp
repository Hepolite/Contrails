
#include "WorldQuery.h"

#include "world/detail/Limits.h"

unsigned int world::data::WorldQuery::count() const
{
	unsigned int blocks = 0u;
	for (const auto & it : m_data)
		blocks += it.second.size();
	return blocks;
}

void world::data::WorldQuery::add(const glm::ivec3 & cpos, ChunkQuery && query)
{
	if (query.empty() || m_memuse + query.memuse() > MAX_QUERY_BYTE_SIZE)
		return;
	m_memuse += query.memuse();
	m_data[cpos] = std::move(query);
}
void world::data::WorldQuery::add(const glm::ivec3 & pos)
{
	add(pos, BlockData{});
}
void world::data::WorldQuery::add(const glm::ivec3 & pos, const BlockData & block, const ColorData & color)
{
	const auto cpos = pos >> CHUNK_SIZE_LG<int>;
	auto & query = m_data[cpos];
	const auto oldMemuse = query.memuse();
	query.add(pos & CHUNK_SIZE_BITS<int>, block, color);
	m_memuse += query.memuse() - oldMemuse;
}

bool world::data::WorldQuery::has(const glm::ivec3 & pos) const
{
	const auto it = m_data.find(pos >> CHUNK_SIZE_LG<int>);
	if (it == m_data.end())
		return false;
	return it->second.has(pos & CHUNK_SIZE_BITS<int>);
}