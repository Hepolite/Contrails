
#include "Shape.h"

#include "util/MathGeneric.h"

void editor::util::Shape::stretch(const glm::ivec3 & start, const glm::ivec3 & end)
{
	const auto delta = end - start;
	setPos(math::min(start, end) + (math::abs(delta) >> 1));
	setSize(delta + math::signp(delta));
}
void editor::util::Shape::setPos(const glm::ivec3 & pos)
{
	m_pos = pos;
}
void editor::util::Shape::setSize(const glm::ivec3 & size)
{
	if (size.x == 0 || size.y == 0 || size.z == 0)
		throw std::invalid_argument("Shape size cannot be zero");
	m_updateMesh |= m_size != size;
	m_size = size;
}

glm::ivec3 editor::util::Shape::getStart() const
{
	return m_pos - ((m_size - math::sign(m_size)) >> 1);
}
glm::ivec3 editor::util::Shape::getEnd() const
{
	return getStart() + m_size - math::sign(m_size);
}

void editor::util::Shape::updateMesh() const
{
	if (m_mesh != nullptr && !m_updateMesh)
		return;
	m_mesh = std::make_unique<render::Mesh<glm::vec3>>();
	m_mesh->setRenderMode(render::opengl::RenderMode::LINES);
	m_mesh->addAttribute({ 0u, render::opengl::DataFormat::FLOAT, 3, 0u });
	mesh(m_mesh->getVertexData(), m_mesh->getIndiceData());
	m_mesh->build();
	m_updateMesh = false;
}

// ...

void editor::util::detail::meshLine(const glm::vec3 & start, const glm::vec3 & end, Vertices & vertices, Indices & indices)
{
	vertices.push_back(start);
	vertices.push_back(end);
	indices.push_back(indices.size());
	indices.push_back(indices.size());
}
void editor::util::detail::meshRectangle(const glm::vec3 & start, const glm::vec3 & end, Vertices & vertices, Indices & indices)
{
	// Along x-axis
	meshLine({ start.x, start.y, start.z }, { end.x, start.y, start.z }, vertices, indices);
	meshLine({ start.x, end.y, start.z }, { end.x, end.y, start.z }, vertices, indices);
	meshLine({ start.x, start.y, end.z }, { end.x, start.y, end.z }, vertices, indices);
	meshLine({ start.x, end.y, end.z }, { end.x, end.y, end.z }, vertices, indices);

	// Along y-axis
	meshLine({ start.x, start.y, start.z }, { start.x, end.y, start.z }, vertices, indices);
	meshLine({ end.x, start.y, start.z }, { end.x, end.y, start.z }, vertices, indices);
	meshLine({ start.x, start.y, end.z }, { start.x, end.y, end.z }, vertices, indices);
	meshLine({ end.x, start.y, end.z }, { end.x, end.y, end.z }, vertices, indices);

	// Along z-axis
	meshLine({ start.x, start.y, start.z }, { start.x, start.y, end.z }, vertices, indices);
	meshLine({ end.x, start.y, start.z }, { end.x, start.y, end.z }, vertices, indices);
	meshLine({ start.x, end.y, start.z }, { start.x, end.y, end.z }, vertices, indices);
	meshLine({ end.x, end.y, start.z }, { end.x, end.y, end.z }, vertices, indices);
}
