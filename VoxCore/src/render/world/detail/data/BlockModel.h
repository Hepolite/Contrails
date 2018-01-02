
#pragma once

#include "world/util/Side.h"

#include <glm/vec3.hpp>
#include <vector>

namespace render
{
	namespace world
	{
		namespace data
		{
			struct BlockModelVertex
			{
				glm::vec3 m_position;
				glm::vec3 m_normal;
				glm::vec3 m_uv;
				glm::vec3 m_color;
			};

			struct BlockModel
			{
				std::vector<BlockModelVertex> m_vertices[::world::util::SIDE_COUNT];
				std::vector<unsigned int> m_indices[::world::util::SIDE_COUNT];
			};
		}
	}
}