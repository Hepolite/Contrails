
#pragma once

#include "io/File.h"
#include "io/Folder.h"
#include "render/world/BlockRender.h"
#include "render/world/BlockRenderRegistry.h"
#include "render/world/BlockTextureAtlas.h"
#include "world/BlockRegistry.h"

#include <glm/vec3.hpp>
#include <pugixml/pugixml.hpp>

namespace render
{
	namespace world
	{
		class BlockRenderLoader
		{
		public:
			inline void injectBlockRegistry(const ::world::BlockRegistry & registry) { m_registry = &registry; }
			inline void injectBlocks(BlockRenderRegistry & blocks) { m_blocks = &blocks; }
			inline void injectTextureAtlas(BlockTextureAtlas & atlas) { m_atlas = &atlas; }

			void loadBlocks(const io::Folder & folder) const;
			void loadBlock(const io::File & file) const;

		private:
			const ::world::BlockRegistry * m_registry = nullptr;
			BlockRenderRegistry * m_blocks = nullptr;
			BlockTextureAtlas * m_atlas = nullptr;
		};

		class BlockRenderVariantLoader
		{
		public:
			inline void injectTextureAtlas(BlockTextureAtlas & atlas) { m_atlas = &atlas; }

			void loadVariant(const pugi::xml_node & variant);
			void loadModel(const pugi::xml_node & model);
			void loadTexture(const pugi::xml_node & texture);
			void loadOcclusion(const pugi::xml_node & occlusion);

			inline auto extractBlock() { return m_block; }

		private:
			BlockTextureAtlas * m_atlas = nullptr;

			data::BlockRender m_block;
		};
	}
}