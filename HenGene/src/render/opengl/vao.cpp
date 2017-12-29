
#include "vao.h"

#include "render/opengl/OpenGL.h"

#include <utility>

namespace
{
	unsigned int binding = 0u;

	inline void setBoundHandle(unsigned int handle)
	{
		glBindVertexArray(handle);
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

render::opengl::vao::vao()
{
	glGenVertexArrays(1, &m_handle);
}
render::opengl::vao::~vao()
{
	if (m_handle != 0u)
	{
		unbind();
		glDeleteVertexArrays(1, &m_handle);
	}
}
render::opengl::vao::vao(vao && other)
{
	*this = std::move(other);
}
render::opengl::vao & render::opengl::vao::operator=(vao && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

bool render::opengl::vao::bind() const
{
	if (!validateBindingHandle(m_handle))
		return false;
	setBoundHandle(m_handle);
	return !HAS_GL_ERROR;
}
bool render::opengl::vao::unbind() const
{
	if (!validateUnbindingHandle(m_handle))
		return false;
	setBoundHandle(0u);
	return !HAS_GL_ERROR;
}
