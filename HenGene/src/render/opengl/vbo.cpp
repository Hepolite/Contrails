
#include "vbo.h"

#include "render/opengl/OpenGL.h"

#include <plog/Log.h>
#include <unordered_map>
#include <utility>

namespace
{
	std::unordered_map<render::opengl::BufferType, unsigned int> bindings;

	inline auto getBoundHandle(render::opengl::BufferType type)
	{
		const auto it = bindings.find(type);
		return it == bindings.end() ? 0u : it->second;
	}
	inline void setBoundHandle(render::opengl::BufferType type, unsigned int handle)
	{
		glBindBuffer(static_cast<GLenum>(type), handle);
		bindings[type] = handle;
	}

	inline bool validateBindingHandle(render::opengl::BufferType type, unsigned int handle)
	{
		const auto boundHandle = getBoundHandle(type);
		return (handle != 0u && (handle != boundHandle || boundHandle == 0u));
	}
	inline bool validateUnbindingHandle(render::opengl::BufferType type, unsigned int handle)
	{
		return handle == getBoundHandle(type);
	}
	inline bool validateBufferingHandle(render::opengl::BufferType type, unsigned int handle)
	{
		return handle != 0u && handle == getBoundHandle(type);
	}
}

render::opengl::vbo::vbo()
	: vbo(BufferType::ARRAY_BUFFER, BufferUse::STATIC_DRAW)
{}
render::opengl::vbo::vbo(BufferType type, BufferUse use)
	: m_type(type), m_use(use)
{
	glGenBuffers(1, &m_handle);
}
render::opengl::vbo::~vbo()
{
	if (m_handle != 0u)
	{
		unbind();
		glDeleteBuffers(1, &m_handle);
	}
}
render::opengl::vbo::vbo(vbo && other)
{
	*this = std::move(other);
}

render::opengl::vbo & render::opengl::vbo::operator=(vbo && other)
{
	if (this != &other)
	{
		std::swap(m_handle, other.m_handle);
		std::swap(m_type, other.m_type);
		std::swap(m_use, other.m_use);
	}
	return *this;
}

bool render::opengl::vbo::bind() const
{
	if (!validateBindingHandle(m_type, m_handle))
		return false;
	setBoundHandle(m_type, m_handle);
	return !HAS_GL_ERROR;
}
bool render::opengl::vbo::unbind() const
{
	if (!validateUnbindingHandle(m_type, m_handle))
		return false;
	setBoundHandle(m_type, 0u);
	return !HAS_GL_ERROR;
}

bool render::opengl::vbo::reserve(unsigned int bytes) const
{
	return reserve(bytes, nullptr);
}
bool render::opengl::vbo::reserve(unsigned int bytes, const void * data) const
{
	if (!validateBufferingHandle(m_type, m_handle))
		return false;
	glBufferData(static_cast<GLenum>(m_type), bytes, data, static_cast<GLenum>(m_use));
	return !HAS_GL_ERROR;
}
bool render::opengl::vbo::buffer(unsigned int bytes, const void * data, unsigned int offset) const
{
	if (!validateBufferingHandle(m_type, m_handle))
		return false;
	glBufferSubData(static_cast<GLenum>(m_type), offset, bytes, data);
	return !HAS_GL_ERROR;
}
bool render::opengl::vbo::retrieve(unsigned int bytes, void * data, unsigned int offset) const
{
	if (!validateBufferingHandle(m_type, m_handle))
		return false;
	glGetBufferSubData(static_cast<GLenum>(m_type), offset, bytes, data);
	return !HAS_GL_ERROR;
}