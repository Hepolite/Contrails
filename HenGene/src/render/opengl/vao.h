
#pragma once

namespace render
{
	namespace opengl
	{
		class vao
		{
		public:
			vao();
			vao(const vao &) = delete;
			vao(vao && other);
			~vao();

			vao & operator=(const vao &) = delete;
			vao & operator=(vao && other);

			bool bind() const;
			bool unbind() const;

			inline auto getHandle() const { return m_handle; }

		private:
			unsigned int m_handle = 0u;
		};
	}
}