
#include "Texture.h"

#include "render/opengl/OpenGL.h"

#include <unordered_map>
#include <utility>

namespace
{
	std::unordered_map<render::opengl::TextureType, unsigned int> bindings;

	inline auto getBoundHandle(render::opengl::TextureType type)
	{
		const auto it = bindings.find(type);
		return it == bindings.end() ? 0u : it->second;
	}
	inline void setBoundHandle(render::opengl::TextureType type, unsigned int handle)
	{
		glBindTexture(static_cast<GLenum>(type), handle);
		bindings[type] = handle;
	}

	inline bool validateBindingHandle(render::opengl::TextureType type, unsigned int handle)
	{
		const auto boundHandle = getBoundHandle(type);
		return (handle != 0u && (handle != boundHandle || boundHandle == 0u));
	}
	inline bool validateUnbindingHandle(render::opengl::TextureType type, unsigned int handle)
	{
		return handle == getBoundHandle(type);
	}
	inline bool validateBufferingHandle(render::opengl::TextureType type, unsigned int handle)
	{
		return handle != 0u && handle == getBoundHandle(type);
	}
}

render::opengl::Texture::Texture(TextureType type)
	: m_type(type)
{
	glGenTextures(1, &m_handle);
}
render::opengl::Texture::~Texture()
{
	if (m_handle != 0)
	{
		unbind();
		glDeleteTextures(1, &m_handle);
	}
}
render::opengl::Texture::Texture(Texture && other)
{
	*this = std::move(other);
}
render::opengl::Texture & render::opengl::Texture::operator=(Texture && other)
{
	if (this != &other)
	{
		std::swap(m_handle, other.m_handle);
		std::swap(m_type, other.m_type);
	}
	return *this;
}

bool render::opengl::Texture::bind() const
{
	if (!validateBindingHandle(m_type, m_handle))
		return false;
	setBoundHandle(m_type, m_handle);
	return !HAS_GL_ERROR;
}
bool render::opengl::Texture::unbind() const
{
	if (!validateUnbindingHandle(m_type, m_handle))
		return false;
	setBoundHandle(m_type, 0u);
	return !HAS_GL_ERROR;
}
