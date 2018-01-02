
#pragma once

#include "io/File.h"
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
			void loadTexture(const io::File & file);
			void loadTexture(const pugi::xml_node & node);
			void loadDefaultConnection(const pugi::xml_node & node);

			inline auto extractTexture() { return m_texture; }

		private:
			data::BlockTexture m_texture;
		};
	}
}