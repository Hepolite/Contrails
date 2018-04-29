
#include "ShapeLine.h"

#include "world/util/Query.h"
#include "world/util/Raytrace.h"
#include "util/MathGeneric.h"

world::data::WorldQuery editor::util::ShapeLine::query(const world::Block & block) const
{
	return world::util::Query{}.writeLine(block, getStart(), getEnd());
}
void editor::util::ShapeLine::mesh(Vertices & vertices, Indices & indices) const
{
	const auto min = getStart() - getPos();
	const auto max = getEnd() - getPos();

	glm::ivec3 pos = min;
	glm::ivec3 delta{ 0 };

	world::util::RaytraceBresenham ray{ min, max };
	do
	{
		ray.next();

		const auto dir = ray.getPos() - ray.getOldPos();
		if (!ray.isValid() || math::abs(dir.x) + math::abs(dir.y) + math::abs(dir.z) != 1)
		{
			const auto lower = math::min(pos, ray.getOldPos());
			const auto higher = math::max(pos, ray.getOldPos());
			detail::meshRectangle(lower, higher + 1, vertices, indices);

			pos = ray.getPos();
			delta = { 0 };
		}
		else
			delta += dir;
	} while (ray.isValid());
}
