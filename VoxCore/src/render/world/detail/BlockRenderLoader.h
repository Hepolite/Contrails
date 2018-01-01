
#pragma once

#include "io/File.h"
#include "io/Folder.h"
#include "render/world/BlockRender.h"
#include "render/world/BlockRenderRegistry.h"

#include <pugixml/pugixml.hpp>

namespace render
{
	namespace world
	{
		class BlockRenderLoader
		{
		public:
			inline void injectBlockRegistry(BlockRenderRegistry & registry) { m_registry = &registry; }

			void loadBlocks(const io::Folder & folder) const;
			void loadBlock(const io::File & file) const;

		private:
			BlockRenderRegistry * m_registry = nullptr;
		};

		class BlockRenderVariantLoader
		{
		public:
			void loadVariant(data::BlockRender & block, const pugi::xml_node & variant, const pugi::xml_node & def) const;

		private:
			void loadModel(data::BlockRender & block, const pugi::xml_node & model, const pugi::xml_node & def) const;
			void loadTexture(data::BlockRender & block, const pugi::xml_node & texture, const pugi::xml_node & def) const;
			void loadOcclusion(data::BlockRender & block, const pugi::xml_node & occlusion, const pugi::xml_node & def) const;
		};
	}
}