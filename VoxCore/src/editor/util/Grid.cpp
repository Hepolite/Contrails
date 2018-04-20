
#include "Grid.h"

#include "util/MathGeneric.h"

void editor::util::Grid::setPos(const glm::vec3 & pos)
{
	m_pos = pos;
	updateMesh();
}
void editor::util::Grid::setSize(float size)
{
	if (size <= 0.0f)
		throw std::invalid_argument("Size cannot be null or negative");
	m_size = size;
	updateMesh();
}
void editor::util::Grid::setResolution(float resolution)
{
	if (resolution <= 0.0f)
		throw std::invalid_argument("Resolution cannot be null or negative");
	m_resolution = resolution;
	updateMesh();
}

void editor::util::Grid::updateMesh()
{
	m_mesh = std::make_unique<render::Mesh<glm::vec3>>();
	m_mesh->setRenderMode(render::opengl::RenderMode::LINES);
	m_mesh->addAttribute({ 0u, render::opengl::DataFormat::FLOAT, 3, 0u });

	auto & vertices = m_mesh->getVertexData();
	auto & indices = m_mesh->getIndiceData();
	for (float i = -0.5f * m_size; i <= 0.5f * m_size; i += m_resolution)
	{
		vertices.emplace_back(i, -0.5f * m_size, m_pos.z);
		vertices.emplace_back(i, 0.5f * m_size, m_pos.z);
		vertices.emplace_back(-0.5f * m_size, i, m_pos.z);
		vertices.emplace_back(0.5f * m_size, i, m_pos.z);

		indices.emplace_back(indices.size());
		indices.emplace_back(indices.size());
		indices.emplace_back(indices.size());
		indices.emplace_back(indices.size());
	}

	for (float i = 0.0f; i <= math::abs(m_pos.z); i += m_resolution)
	{
		vertices.emplace_back(m_pos.x - 0.5f * m_resolution, m_pos.y, i);
		vertices.emplace_back(m_pos.x + 0.5f * m_resolution, m_pos.y, i);
		vertices.emplace_back(m_pos.x, m_pos.y - 0.5f * m_resolution, i);
		vertices.emplace_back(m_pos.x, m_pos.y + 0.5f * m_resolution, i);

		indices.emplace_back(indices.size());
		indices.emplace_back(indices.size());
		indices.emplace_back(indices.size());
		indices.emplace_back(indices.size());
	}
	vertices.emplace_back(m_pos.x, m_pos.y, 0.0f);
	vertices.emplace_back(m_pos.x, m_pos.y, m_pos.z);
	indices.emplace_back(indices.size());
	indices.emplace_back(indices.size());

	m_mesh->build();
}
