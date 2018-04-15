
#pragma once

#include "io/File.h"
#include "io/Folder.h"
#include "world/render/BlockRender.h"
#include "world/render/BlockRenderRegistry.h"
#include "world/render/BlockTextureAtlas.h"
#include "world/BlockRegistry.h"

#include <glm/vec3.hpp>
#include <pugixml/pugixml.hpp>

namespace world
{
	namespace render
	{
		class BlockRenderLoader
		{
		public:
			inline void inject(const BlockRegistry & registry) { m_registry = &registry; }
			inline void inject(BlockRenderRegistry & blocks) { m_blocks = &blocks; }
			inline void inject(BlockTextureAtlas & atlas) { m_atlas = &atlas; }

			void loadBlocks(const io::Folder & folder) const;
			void loadBlock(const io::File & file) const;

		private:
			const BlockRegistry * m_registry = nullptr;
			BlockRenderRegistry * m_blocks = nullptr;
			BlockTextureAtlas * m_atlas = nullptr;
		};

		class BlockRenderVariantLoader
		{
		public:
			inline void inject(const BlockRegistry & registry) { m_registry = &registry; }
			inline void inject(BlockTextureAtlas & atlas) { m_atlas = &atlas; }

			void loadVariant(const pugi::xml_node & variant);
			void loadModel(const pugi::xml_node & model);
			void loadTexture(const pugi::xml_node & texture);
			void loadOcclusion(const pugi::xml_node & occlusion);

			inline auto extractBlock() { return m_block; }

		private:
			const BlockRegistry * m_registry = nullptr;
			BlockTextureAtlas * m_atlas = nullptr;

			data::BlockRender m_block;
		};
	}
}