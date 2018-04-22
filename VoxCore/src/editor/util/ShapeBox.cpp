
#include "ShapeBox.h"

#include "world/util/Query.h"
#include "util/MathGeneric.h"

world::data::WorldQuery editor::util::ShapeBox::query(const world::Block & block) const
{
	return world::util::Query{}.writeRectangle(block, getStart(), getEnd());
}
void editor::util::ShapeBox::mesh(std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices) const
{
	const auto s = math::min(getStart(), getEnd());
	const auto e = math::max(getStart(), getEnd()) + 1;

	vertices.push_back(s);
	vertices.emplace_back(e.x, s.y, s.z);
	vertices.emplace_back(s.x, e.y, s.z);
	vertices.emplace_back(e.x, e.y, s.z);
	vertices.emplace_back(s.x, s.y, e.z);
	vertices.emplace_back(e.x, s.y, e.z);
	vertices.emplace_back(s.x, e.y, e.z);
	vertices.push_back(e);

	indices.push_back(0); indices.push_back(1);
	indices.push_back(2); indices.push_back(3);
	indices.push_back(4); indices.push_back(5);
	indices.push_back(6); indices.push_back(7);

	indices.push_back(0); indices.push_back(2);
	indices.push_back(1); indices.push_back(3);
	indices.push_back(4); indices.push_back(6);
	indices.push_back(5); indices.push_back(7);

	indices.push_back(0); indices.push_back(4);
	indices.push_back(1); indices.push_back(5);
	indices.push_back(2); indices.push_back(6);
	indices.push_back(3); indices.push_back(7);
}
