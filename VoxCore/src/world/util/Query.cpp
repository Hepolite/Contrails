
#include "Query.h"

#include "world/detail/Limits.h"
#include "world/util/Raytrace.h"
#include "util/Maths.h"

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
world::data::WorldQuery world::util::Query::readCylinder(const glm::ivec3 & start, const glm::ivec3 & end, math::Axis axis) const
{
	return writeCylinder({}, start, end, axis);
}
world::data::WorldQuery world::util::Query::readRectangle(const glm::ivec3 & start, const glm::ivec3 & end) const
{
	return writeRectangle({}, start, end);
}
world::data::WorldQuery world::util::Query::readLine(const glm::ivec3 & start, const glm::ivec3 & end) const
{
	return writeLine({}, start, end);
}

world::data::WorldQuery world::util::Query::writeBlock(const Block & block, const glm::ivec3 & pos) const
{
	data::WorldQuery query;
	query.add(pos, getBlockData(block), getColorData(block));
	return query;
}
world::data::WorldQuery world::util::Query::writeCylinder(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end, math::Axis axis) const
{
	const auto min = math::min(start, end);
	const auto max = math::max(start, end);
	const auto cmin = min >> data::CHUNK_SIZE_LG<int>;
	const auto cmax = max >> data::CHUNK_SIZE_LG<int>;

	const auto dim = axis == math::Axis::Z ? glm::uvec2{ 0, 1 } : axis == math::Axis::Y ? glm::uvec2{ 0, 2 } : glm::uvec2{ 1, 2 };
	const auto size = max - min + 1;
	
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

		const auto center = glm::vec3{ min - cpos * data::CHUNK_SIZE<int> } + 0.5f * glm::vec3{ size };

		data::ChunkQuery chunkQuery;

		glm::ivec3 pos;
		for (pos.x = lower.x; pos.x <= upper.x; ++pos.x)
		for (pos.y = lower.y; pos.y <= upper.y; ++pos.y)
		for (pos.z = lower.z; pos.z <= upper.z; ++pos.z)
		{
			const auto& delta = math::pow(2.0f * (0.5f + glm::vec3{ pos } - center) / glm::vec3{ size }, 2.0f);
			if (delta[dim.x] + delta[dim.y] <= 1.0f)
				chunkQuery.add(pos, blockData, colorData);
		}

		query.add(cpos, std::move(chunkQuery));
	}
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
world::data::WorldQuery world::util::Query::writeLine(const Block & block, const glm::ivec3 & start, const glm::ivec3 & end) const
{
	const auto blockData = getBlockData(block);
	const auto colorData = getColorData(block);

	data::WorldQuery query;
	for (util::RaytraceBresenham ray{ start, end }; ray.isValid(); ray.next())
		query.add(ray.getPos(), blockData, colorData);
	return query;
}
