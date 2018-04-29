
#include "ShapeCylinder.h"

#include "world/util/Query.h"
#include "util/MathGeneric.h"

world::data::WorldQuery editor::util::ShapeCylinder::query(const world::Block & block) const
{
	return world::util::Query{}.writeCylinder(block, getStart(), getEnd(), getAxis());
}
void editor::util::ShapeCylinder::mesh(Vertices & vertices, Indices & indices) const
{
	const auto min = math::min(getStart(), getEnd()) - getPos();
	const auto max = math::max(getStart(), getEnd()) - getPos();
	detail::meshRectangle(min, max + 1, vertices, indices);
}
