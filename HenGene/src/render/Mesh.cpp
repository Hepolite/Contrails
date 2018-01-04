
#include "Mesh.h"

#include "render/opengl/OpenGL.h"

bool render::MeshBase::build(unsigned int indices, unsigned int vertices, const void * indiceData, const void * vertexData)
{
	m_indiceCount = indices;
	m_vao.bind();

	m_vertex.bind();
	m_vertex.reserve(vertices * m_size, vertexData);
	m_indice.bind();
	m_indice.reserve(indices * sizeof(unsigned int), indiceData);
	for (const auto& attribute : m_attributes)
		attribute.enable(m_size);

	m_vao.unbind();
	return true;
}

void render::MeshBase::render() const
{
	if (m_indiceCount != 0u)
	{
		m_vao.bind();
		glDrawElements(static_cast<GLenum>(m_mode), m_indiceCount, GL_UNSIGNED_INT, nullptr);
	}
}