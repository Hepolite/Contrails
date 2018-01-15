
#include "Query.h"

#include "world/detail/Limits.h"
#include "util/MathGeneric.h"

world::data::BlockData world::util::Query::getBlockData(const Block & block) const
{
	return { block.m_id, block.m_lightEmitted.a };
}
world::data::ColorData world::util::Query::getColorData(const Block & block) const
{
	return { { block.m_lightEmitted.r, block.m_lightEmitted.g, block.m_lightEmitted.b } };
}

world::data::WorldQuery world::util::Query::readBlock(const glm::ivec3 & pos) const
{
	return writeBlock({}, pos);
}
world::data::WorldQuery world::util::Query::readRectangle(const glm::ivec3 & start, const glm::ivec3 & end) const
{
	return writeRectangle({}, start, end);
}

world::data::WorldQuery world::util::Query::writeBlock(const Block & block, const glm::ivec3 & pos) const
{
	data::WorldQuery query;
	query.add(pos, getBlockData(block), getColorData(block));
	return query;
}
world::data::WorldQuery world::util::Query::writeRectangle(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end) const
{
	const auto min = math::min(start, end);
	const auto max = math::max(start, end);
	const auto cmin = min >> data::CHUNK_SIZE_LG<int>;
	const auto cmax = max >> data::CHUNK_SIZE_LG<int>;

	const auto blockData = getBlockData(block);
	const auto colorData = getColorData(block);

	data::WorldQuery query;
	glm::ivec3 cpos;
	for (cpos.z = cmin.z; cpos.z <= cmax.z; ++cpos.z)
	for (cpos.y = cmin.y; cpos.y <= cmax.y; ++cpos.y)
	for (cpos.x = cmin.x; cpos.x <= cmax.x; ++cpos.x)
	{
		const auto lower = math::max(min - cpos * data::CHUNK_SIZE<int>, glm::ivec3{});
		const auto upper = math::min(max - cpos * data::CHUNK_SIZE<int>, glm::ivec3{ data::CHUNK_SIZE_BITS<int> });

		data::ChunkQuery chunkQuery;
		chunkQuery.add(lower, upper, blockData, colorData);
		query.add(cpos, std::move(chunkQuery));
	}
	return query;
}
