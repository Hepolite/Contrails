
#pragma once

#include "render/Mesh.h"
#include "render/RenderPass.h"

#include <array>
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

		using ChunkMesh = std::array<Mesh<ChunkMeshVertex>, RENDER_PASS_COUNT>;
	}
}