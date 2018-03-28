
#pragma once

#include "io/File.h"
#include "render/opengl/Texture.h"

#include <allegro5/bitmap.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace world
{
	namespace render
	{
		class BlockTextureAtlas
		{
		public:
			BlockTextureAtlas() = default;
			~BlockTextureAtlas() { cleanup(); }

			unsigned int attach(const io::File & file);
			unsigned int attach(ALLEGRO_BITMAP * bitmap);
			bool build();

			inline auto bind() const { return m_handle.bind(); }

		private:
			unsigned int attach(ALLEGRO_BITMAP * bitmap, bool owned);
			void cleanup();

			::render::opengl::Texture m_handle{ ::render::opengl::TextureType::TEXTURE_2D_ARRAY };

			std::unordered_map<std::string, unsigned int> m_files;
			std::vector<ALLEGRO_BITMAP*> m_ownedBitmaps;
			std::vector<ALLEGRO_BITMAP*> m_bitmaps;

			bool m_built = false;
			unsigned int m_width = 0u;
			unsigned int m_height = 0u;
			unsigned int m_depth = 0u;
		};
	}
}