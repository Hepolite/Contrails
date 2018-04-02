
#pragma once

#include "render/Mesh.h"
#include "render/RenderPass.h"

#include <array>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace world
{
	namespace render
	{
		struct ChunkMeshVertex
		{
			glm::vec3 m_pos;
			glm::vec3 m_normal;
			glm::vec3 m_uv;
			glm::vec4 m_color;
			unsigned int m_texture;
		};

		using ChunkMesh = std::array<::render::Mesh<ChunkMeshVertex>, ::render::RENDER_PASS_COUNT>;
	}
}