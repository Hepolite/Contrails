
#include "WorldQuery.h"

#include "world/detail/Limits.h"

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
