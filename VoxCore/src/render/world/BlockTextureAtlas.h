
#pragma once

#include "render/opengl/Texture.h"

namespace render
{
	namespace world
	{
		class BlockTextureAtlas
		{
		public:


		private:
			opengl::Texture m_texture{ opengl::TextureType::TEXTURE_2D_ARRAY };
		};
	}
}