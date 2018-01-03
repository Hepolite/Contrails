
#include "fbo.h"

#include "render/opengl/OpenGL.h"

#include <utility>

namespace
{
	unsigned int binding = 0u;

	inline void setBoundHandle(unsigned int handle)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, handle);
		binding = handle;
	}

	inline bool validateBindingHandle(unsigned int handle)
	{
		return (handle != 0u && (handle != binding || binding == 0u));
	}
	inline bool validateUnbindingHandle(unsigned int handle)
	{
		return handle == binding;
	}
}

render::opengl::fbo::fbo()
{
	glGenFramebuffers(1, &m_handle);
}
render::opengl::fbo::~fbo()
{
	if (m_handle != 0u)
	{
		unbind();
		glDeleteFramebuffers(1, &m_handle);
	}
}
render::opengl::fbo::fbo(fbo && other)
{
	*this = std::move(other);
}

render::opengl::fbo & render::opengl::fbo::operator=(fbo && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

bool render::opengl::fbo::bind() const
{
	if (!validateBindingHandle(m_handle))
		return false;
	setBoundHandle(m_handle);
	return !HAS_GL_ERROR;
}

bool render::opengl::fbo::unbind() const
{
	if (!validateUnbindingHandle(m_handle))
		return false;
	setBoundHandle(0u);
	return !HAS_GL_ERROR;
}
