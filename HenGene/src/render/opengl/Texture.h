
#pragma once

#include "render/opengl/Enums.h"

namespace render
{
	namespace opengl
	{
		class Texture
		{
		public:
			Texture() = delete;
			Texture(TextureType type);
			Texture(const Texture &) = delete;
			Texture(Texture && other);
			~Texture();

			Texture & operator=(const Texture &) = delete;
			Texture & operator=(Texture && other);

			bool bind() const;
			bool unbind() const;

			inline auto getHandle() const { return m_handle; }

		private:
			unsigned int m_handle = 0u;
			TextureType m_type;
		};
	}
}
