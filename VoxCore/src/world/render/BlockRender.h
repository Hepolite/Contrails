
#pragma once

#include "world/render/detail/data/BlockModel.h"
#include "world/render/detail/data/BlockTexture.h"
#include "world/util/Side.h"

namespace world
{
	namespace render
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