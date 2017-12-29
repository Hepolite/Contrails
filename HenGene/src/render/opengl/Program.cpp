
#include "Program.h"

#include "render/opengl/OpenGL.h"

#include <plog/Log.h>
#include <utility>

namespace
{
	unsigned int binding = 0u;

	inline void setBoundHandle(unsigned int handle)
	{
		glUseProgram(handle);
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

render::opengl::Program::Program(const std::string & name)
	: Program{}
{
	setName(name);
}
render::opengl::Program::Program()
{
	m_handle = glCreateProgram();
}
render::opengl::Program::~Program()
{
	if (m_handle != 0u)
	{
		unbind();
		glDeleteProgram(m_handle);
	}
}
render::opengl::Program::Program(Program && other)
{
	*this = std::move(other);
}
render::opengl::Program & render::opengl::Program::operator=(Program && other)
{
	if (this != &other)
		std::swap(m_handle, other.m_handle);
	return *this;
}

bool render::opengl::Program::attach(const Shader & shader) const
{
	if (m_handle == 0u || shader.getHandle() == 0u)
		return false;
	glAttachShader(m_handle, shader.getHandle());
	return !HAS_GL_ERROR;
}
bool render::opengl::Program::link() const
{
	if (m_handle == 0u)
		return false;
	glLinkProgram(m_handle);

	GLint result;
	glGetProgramiv(m_handle, GL_LINK_STATUS, &result);
	GLint length;
	glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &length);
	std::string message{ "", static_cast<unsigned int>(length) };
	glGetProgramInfoLog(m_handle, length, nullptr, &message[0]);

	if (!result)
	{
		LOG_WARNING << message;
		return false;
	}
	return !HAS_GL_ERROR;
}

bool render::opengl::Program::bind() const
{
	if (!validateBindingHandle(m_handle))
		return false;
	setBoundHandle(m_handle);
	return !HAS_GL_ERROR;
}
bool render::opengl::Program::unbind() const
{
	if (!validateUnbindingHandle(m_handle))
		return false;
	setBoundHandle(0u);
	return !HAS_GL_ERROR;
}
