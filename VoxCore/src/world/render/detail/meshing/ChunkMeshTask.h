
#pragma once

#include "world/detail/data/BlockRegion.h"
#include "world/render/detail/meshing/ChunkMesh.h"

#include <glm/vec3.hpp>
#include <memory>

namespace world
{
	namespace render
	{
		struct ChunkMeshTask
		{
			glm::ivec3 m_cpos;
			::world::data::BlockRegion m_data;

			std::unique_ptr<ChunkMesh> m_mesh;
		};
	}
}