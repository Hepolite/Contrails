
#pragma once

#include "world/render/BlockRender.h"

#include <vector>

namespace world
{
	namespace render
	{
		class BlockRenderRegistry
		{
		public:
			BlockRenderRegistry() = default;
			BlockRenderRegistry(const BlockRenderRegistry &) = delete;
			BlockRenderRegistry(BlockRenderRegistry &&) = delete;
			~BlockRenderRegistry() = default;

			BlockRenderRegistry & operator=(const BlockRenderRegistry &) = delete;
			BlockRenderRegistry & operator=(BlockRenderRegistry &&) = delete;

			data::BlockRender & operator[](const unsigned int & id);
			const data::BlockRender & operator[](const unsigned int & id) const;

		private:
			std::vector<data::BlockRender> m_blocks{ 1u };
		};
	}
}