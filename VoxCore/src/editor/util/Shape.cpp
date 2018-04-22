
#include "Shape.h"

void editor::util::Shape::setPos(const glm::ivec3 & pos)
{
	m_pos = pos;
}
void editor::util::Shape::setSize(const glm::ivec3 & size)
{
	if (size.x <= 0 || size.y <= 0 || size.z <= 0)
		throw std::invalid_argument("Shape size cannot be zero or negative");
	m_size = size;
	updateMesh();
}

void editor::util::Shape::updateMesh()
{
	m_mesh = std::make_unique<render::Mesh<glm::vec3>>();
	m_mesh->setRenderMode(render::opengl::RenderMode::LINES);
	m_mesh->addAttribute({ 0u, render::opengl::DataFormat::FLOAT, 3, 0u });
	mesh(m_mesh->getVertexData(), m_mesh->getIndiceData());
	m_mesh->build();
}
