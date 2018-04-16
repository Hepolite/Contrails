
#pragma once

#include "render/opengl/Attribute.h"
#include "render/opengl/Enums.h"
#include "render/opengl/vao.h"
#include "render/opengl/vbo.h"

#include <vector>

namespace render
{
	class MeshBase
	{
	public:
		inline void setRenderMode(opengl::RenderMode mode) { m_mode = mode; }
		inline void addAttribute(const opengl::Attribute & attr) { m_attributes.push_back(attr); }

		void render() const;

		inline bool empty() const { return m_indiceCount == 0u; }

	protected:
		MeshBase() = delete;
		MeshBase(unsigned int size) : m_size(size) {}
		MeshBase(const MeshBase &) = delete;
		MeshBase(MeshBase &&) = default;
		virtual ~MeshBase() = default;

		MeshBase & operator=(const MeshBase &) = delete;
		MeshBase & operator=(MeshBase &&) = default;

		bool build(unsigned int indices, unsigned int vertices, const void * indiceData, const void * vertexData);

	private:
		opengl::vao m_vao;
		opengl::vbo m_vertex{ opengl::BufferType::ARRAY_BUFFER };
		opengl::vbo m_indice{ opengl::BufferType::ELEMENT_ARRAY_BUFFER };
		opengl::RenderMode m_mode = opengl::RenderMode::TRIANGLES;
		std::vector<opengl::Attribute> m_attributes;

		unsigned int m_size = 0;
		unsigned int m_indiceCount = 0u;
	};

	template<typename Vertex>
	class Mesh : public MeshBase
	{
	public:
		Mesh() : MeshBase(sizeof(Vertex)) {}
		Mesh(const Mesh &) = delete;
		Mesh(Mesh &&) = default;
		virtual ~Mesh() = default;

		Mesh & operator=(const Mesh &) = delete;
		Mesh & operator=(Mesh &&) = default;

		inline std::vector<unsigned int> & getIndiceData() { return m_indices; }
		inline std::vector<Vertex> & getVertexData() { return m_vertices; }

		bool build();
		
	private:
		std::vector<unsigned int> m_indices;
		std::vector<Vertex> m_vertices;
	};
}

template<typename Vertex>
inline bool render::Mesh<Vertex>::build()
{
	if (m_indices.size() == 0 || m_vertices.size() == 0)
		return false;
	return MeshBase::build(m_indices.size(), m_vertices.size(), &m_indices[0u], &m_vertices[0u]);
}