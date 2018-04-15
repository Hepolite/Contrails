
#pragma once

#include "io/File.h"
#include "world/render/BlockTextureAtlas.h"
#include "world/render/detail/data/BlockTexture.h"

#include <glm/vec3.hpp>
#include <pugixml/pugixml.hpp>

namespace world
{
	namespace render
	{
		class BlockTextureLoader
		{
		public:
			inline void injectTextureAtlas(BlockTextureAtlas & atlas) { m_atlas = &atlas; }

			void loadTexture(const io::File & file);
			void loadTexture(const pugi::xml_node & texture);

			void loadConnection(const pugi::xml_node & connection);
			void loadDefaultConnection(const pugi::xml_node & connection);
			void loadRandomConnection(const pugi::xml_node & connection);

			inline auto extractTexture() { return m_texture; }

		private:
			BlockTextureAtlas * m_atlas = nullptr;

			data::BlockTexture m_texture;
		};
	}
}