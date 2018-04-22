
#include "ShapeBox.h"

#include "world/util/Query.h"
#include "util/MathGeneric.h"

world::data::WorldQuery editor::util::ShapeBox::query(const world::Block & block) const
{
	return world::util::Query{}.writeRectangle(block, getStart(), getEnd());
}
void editor::util::ShapeBox::mesh(Vertices & vertices, Indices & indices) const
{
	const auto min = math::min(getStart(), getEnd()) - getPos();
	const auto max = math::max(getStart(), getEnd()) - getPos();
	detail::meshRectangle(min, max + 1, vertices, indices);
}
