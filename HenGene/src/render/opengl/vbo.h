
#pragma once

#include "render/opengl/Enums.h"

namespace render
{
	namespace opengl
	{
		class vbo
		{
		public:
			vbo();
			vbo(BufferType type, BufferUse use = BufferUse::STATIC_DRAW);
			vbo(const vbo &) = delete;
			vbo(vbo && other);
			~vbo();

			vbo & operator=(const vbo &) = delete;
			vbo & operator=(vbo && other);

			bool bind() const;
			bool unbind() const;

			bool reserve(unsigned int bytes) const;
			bool reserve(unsigned int bytes, const void * data) const;
			bool buffer(unsigned int bytes, const void * data, unsigned int offset) const;
			bool retrieve(unsigned int bytes, void * data, unsigned int offset) const;

			inline auto getHandle() const { return m_handle; }

		private:
			unsigned int m_handle = 0u;
			BufferType m_type;
			BufferUse m_use;
		};
	}
}