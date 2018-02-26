
#pragma once

#include "render/Mesh.h"
#include "render/RenderPass.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace render
{
	namespace world
	{
		struct ChunkMeshVertex
		{
			glm::vec3 m_pos;
			glm::vec3 m_normal;
			glm::vec3 m_uv;
			glm::vec4 m_color;
		};

		struct ChunkMesh
		{
			Mesh<ChunkMeshVertex> m_meshes[RENDER_PASS_COUNT];
		};
	}
}