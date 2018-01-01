
#pragma once

#include "render/world/detail/data/BlockModel.h"
#include "render/world/detail/data/BlockTexture.h"
#include "world/util/Side.h"

namespace render
{
	namespace world
	{
		namespace data
		{
			struct BlockRender
			{
				BlockModel m_model;
				BlockTexture m_texture[::world::util::SIDE_COUNT];

				bool m_occlude[::world::util::SIDE_COUNT] = { false };
			};
		}
	}
}