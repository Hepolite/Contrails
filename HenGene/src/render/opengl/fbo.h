
#pragma once

namespace render
{
	namespace opengl
	{
		class fbo
		{
		public:
			fbo();
			fbo(const fbo &) = delete;
			fbo(fbo && other);
			~fbo();

			fbo & operator=(const fbo &) = delete;
			fbo & operator=(fbo && other);

			bool bind() const;
			bool unbind() const;

			inline auto getHandle() const { return m_handle; }

		private:
			unsigned int m_handle = 0u;
		};
	}
}