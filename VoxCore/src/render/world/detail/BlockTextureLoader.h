
#pragma once

#include "io/File.h"
#include "render/world/BlockTextureAtlas.h"
#include "render/world/detail/data/BlockTexture.h"

#include <glm/vec3.hpp>
#include <pugixml/pugixml.hpp>

namespace render
{
	namespace world
	{
		class BlockTextureLoader
		{
		public:
			inline void injectTextureAtlas(BlockTextureAtlas & atlas) { m_atlas = &atlas; }

			void loadTexture(const io::File & file);
			void loadTexture(const pugi::xml_node & node);
			void loadDefaultConnection(const pugi::xml_node & node);

			inline auto extractTexture() { return m_texture; }

		private:
			BlockTextureAtlas * m_atlas = nullptr;

			data::BlockTexture m_texture;
		};
	}
}