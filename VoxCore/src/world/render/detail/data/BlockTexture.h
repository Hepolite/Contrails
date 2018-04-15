
#pragma once

#include "world/detail/data/BlockRegion.h"
#include "world/render/detail/data/TextureData.h"
#include "world/util/Side.h"

#include <functional>
#include <glm/vec3.hpp>

namespace world
{
	namespace render
	{
		namespace data
		{
			struct BlockTexture
			{
				std::function<TextureData(
					const ::world::data::BlockRegion &,
					const glm::ivec3 &,
					const ::world::util::Side &
				)> m_lookup = nullptr;

				unsigned int m_handle = 0u;
			};
		}
	}
}