
#include "ShapePoint.h"

#include "world/util/Query.h"

world::data::WorldQuery editor::util::ShapePoint::query(const world::Block & block) const
{
	return world::util::Query{}.writeBlock(block, getEnd());
}
void editor::util::ShapePoint::mesh(Vertices & vertices, Indices & indices) const
{
	const auto pos = getEnd();
	detail::meshRectangle(pos, pos + 1, vertices, indices);
}
